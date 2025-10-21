#!/usr/bin/env node

/**
 * Git for Logic - Merged Implementation
 * Content-addressed version control for business logic execution
 * Combines Git internals with deterministic rule evaluation
 */

const fs = require('fs');
const crypto = require('crypto');
const path = require('path');
const yaml = require('js-yaml');
const sqlite3 = require('sqlite3').verbose();

class GitForLogic {
  constructor(repoPath = './logic-repo') {
    this.repoPath = repoPath;
    this.dbPath = path.join(repoPath, '.logicgit', 'state.db');
    this.currentBranch = 'main';
    this.ensureRepoStructure();
  }

  // Initialize repository structure (like git init)
  ensureRepoStructure() {
    const dirs = [
      this.repoPath,
      path.join(this.repoPath, '.logicgit'),
      path.join(this.repoPath, '.logicgit', 'objects'),
      path.join(this.repoPath, '.logicgit', 'refs', 'heads'),
      path.join(this.repoPath, 'rules'),
      path.join(this.repoPath, 'data'),
      path.join(this.repoPath, 'exports')
    ];
    
    dirs.forEach(dir => {
      if (!fs.existsSync(dir)) fs.mkdirSync(dir, { recursive: true });
    });
    
    // Initialize HEAD if it doesn't exist
    const headPath = path.join(this.repoPath, '.logicgit', 'HEAD');
    if (!fs.existsSync(headPath)) {
      fs.writeFileSync(headPath, 'ref: refs/heads/main\n');
    }

    // Initialize main branch if it doesn't exist
    const mainPath = path.join(this.repoPath, '.logicgit', 'refs', 'heads', 'main');
    if (!fs.existsSync(mainPath)) {
      fs.writeFileSync(mainPath, ''); // Empty until first commit
    }
  }

  // Initialize database (lazy loading)
  async initDatabase() {
    if (this.db) return this.db;

    return new Promise((resolve, reject) => {
      this.db = new sqlite3.Database(this.dbPath, (err) => {
        if (err) return reject(err);
        
        this.createTables().then(() => {
          console.log(`🔧 Database initialized: ${this.dbPath}`);
          resolve(this.db);
        }).catch(reject);
      });
    });
  }

  async createTables() {
    const statements = [
      // Git-style objects storage
      `CREATE TABLE IF NOT EXISTS objects (
        hash TEXT PRIMARY KEY,
        type TEXT NOT NULL,
        content TEXT NOT NULL,
        size INTEGER,
        created_at DATETIME DEFAULT CURRENT_TIMESTAMP
      )`,
      
      // Execution history (like git log)
      `CREATE TABLE IF NOT EXISTS executions (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        execution_hash TEXT UNIQUE NOT NULL,
        commit_hash TEXT,
        parent_hash TEXT,
        rules_file TEXT NOT NULL,
        rules_hash TEXT NOT NULL,
        input_hash TEXT NOT NULL,
        output_hash TEXT NOT NULL,
        applied_rules TEXT NOT NULL,
        execution_time_ms INTEGER,
        branch TEXT DEFAULT 'main',
        message TEXT,
        author TEXT DEFAULT 'logic-git',
        timestamp DATETIME DEFAULT CURRENT_TIMESTAMP
      )`,

      // Audit trail (MNEME-style)
      `CREATE TABLE IF NOT EXISTS audit_trail (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        execution_hash TEXT REFERENCES executions(execution_hash),
        rule_name TEXT NOT NULL,
        condition_text TEXT NOT NULL,
        changes_json TEXT NOT NULL,
        state_before TEXT,
        state_after TEXT,
        timestamp DATETIME DEFAULT CURRENT_TIMESTAMP
      )`,

      // State snapshots for debugging
      `CREATE TABLE IF NOT EXISTS state_snapshots (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        execution_hash TEXT REFERENCES executions(execution_hash),
        snapshot_type TEXT DEFAULT 'final',
        state_data TEXT NOT NULL,
        state_hash TEXT NOT NULL,
        timestamp DATETIME DEFAULT CURRENT_TIMESTAMP
      )`
    ];

    const indexes = [
      `CREATE INDEX IF NOT EXISTS idx_executions_hash ON executions(execution_hash)`,
      `CREATE INDEX IF NOT EXISTS idx_executions_time ON executions(timestamp)`,
      `CREATE INDEX IF NOT EXISTS idx_executions_branch ON executions(branch)`,
      `CREATE INDEX IF NOT EXISTS idx_audit_execution ON audit_trail(execution_hash)`
    ];

    // Execute statements
    for (const stmt of [...statements, ...indexes]) {
      await new Promise((resolve, reject) => {
        this.db.run(stmt, (err) => err ? reject(err) : resolve());
      });
    }
  }

  // Content-addressed storage (Git-style)
  async hashObject(content, type = 'blob') {
    await this.initDatabase();
    
    const contentStr = typeof content === 'string' ? content : JSON.stringify(content, null, 2);
    const header = `${type} ${contentStr.length}\0`;
    const hash = crypto.createHash('sha1').update(header + contentStr).digest('hex');
    
    // Store in database
    await new Promise((resolve, reject) => {
      this.db.run(
        'INSERT OR REPLACE INTO objects (hash, type, content, size) VALUES (?, ?, ?, ?)',
        [hash, type, contentStr, contentStr.length],
        (err) => err ? reject(err) : resolve()
      );
    });

    // Also store in filesystem for Git compatibility
    const objectDir = path.join(this.repoPath, '.logicgit', 'objects', hash.substring(0, 2));
    const objectFile = path.join(objectDir, hash.substring(2));
    
    if (!fs.existsSync(objectDir)) {
      fs.mkdirSync(objectDir, { recursive: true });
    }
    
    if (!fs.existsSync(objectFile)) {
      fs.writeFileSync(objectFile, contentStr);
    }

    return hash;
  }

  // Load rules from YAML
  loadRules(filename) {
    const rulesPath = path.join(this.repoPath, 'rules', filename);
    if (!fs.existsSync(rulesPath)) {
      throw new Error(`Rules file not found: ${rulesPath}`);
    }
    
    const content = fs.readFileSync(rulesPath, 'utf8');
    return yaml.load(content);
  }

  // Load data (JSON or CSV)
  loadData(filename) {
    const dataPath = path.join(this.repoPath, 'data', filename);
    if (!fs.existsSync(dataPath)) {
      throw new Error(`Data file not found: ${dataPath}`);
    }

    const content = fs.readFileSync(dataPath, 'utf8');
    
    if (filename.endsWith('.json')) {
      return JSON.parse(content);
    } else if (filename.endsWith('.csv')) {
      return this.parseCsv(content);
    } else {
      throw new Error('Unsupported data format. Use .json or .csv');
    }
  }

  // Simple CSV parser
  parseCsv(content) {
    const lines = content.trim().split('\n');
    const headers = lines[0].split(',').map(h => h.trim().replace(/"/g, ''));
    
    return lines.slice(1).map(line => {
      const values = line.split(',').map(v => v.trim().replace(/"/g, ''));
      const obj = {};
      headers.forEach((header, i) => {
        const value = values[i] || '';
        obj[header] = isNaN(value) || value === '' ? value : Number(value);
      });
      return obj;
    });
  }

  // Evaluate rule conditions
  evaluateCondition(condition, data) {
    try {
      // Simple and safe condition evaluation
      const safeEval = condition.replace(/(\w+\.?\w*)/g, (match) => {
        if (match === 'true' || match === 'false' || match === 'null' || !isNaN(match)) {
          return match;
        }
        return match.includes('.') ? `data.${match}` : `data.${match}`;
      });
      
      // Use Function constructor for safer evaluation
      const func = new Function('data', `return ${safeEval}`);
      return func(data);
    } catch (e) {
      console.warn(`⚠️  Condition evaluation failed: ${condition} - ${e.message}`);
      return false;
    }
  }

  // Set nested object values
  setNestedValue(obj, path, value) {
    const keys = path.split('.');
    let current = obj;
    
    for (let i = 0; i < keys.length - 1; i++) {
      if (!current[keys[i]] || typeof current[keys[i]] !== 'object') {
        current[keys[i]] = {};
      }
      current = current[keys[i]];
    }
    
    current[keys[keys.length - 1]] = value;
  }

  // Execute rules on data (deterministic)
  async executeRules(rulesData, inputData, options = {}) {
    const startTime = Date.now();
    await this.initDatabase();
    
    // Sort rules by priority
    const sortedRules = rulesData.rules.sort((a, b) => (a.priority || 999) - (b.priority || 999));
    
    // Deep clone input to avoid mutation
    let state = JSON.parse(JSON.stringify(inputData));
    const appliedRules = [];
    const auditTrail = [];
    
    console.log(`🚀 Executing ${sortedRules.length} rules`);
    
    for (const rule of sortedRules) {
      const stateBefore = JSON.parse(JSON.stringify(state));
      
      if (this.evaluateCondition(rule.when, state)) {
        console.log(`✅ Applied: ${rule.name}`);
        appliedRules.push(rule.name);
        
        // Apply transformations
        for (const [key, value] of Object.entries(rule.then)) {
          this.setNestedValue(state, key, value);
        }
        
        auditTrail.push({
          rule: rule.name,
          condition: rule.when,
          changes: rule.then,
          stateBefore,
          stateAfter: JSON.parse(JSON.stringify(state)),
          timestamp: new Date().toISOString()
        });
      } else {
        console.log(`⏸️  Skipped: ${rule.name}`);
      }
    }

    const executionTime = Date.now() - startTime;
    
    // Generate hashes
    const rulesHash = this.generateHash(rulesData);
    const inputHash = this.generateHash(inputData);
    const outputHash = this.generateHash(state);
    
    // Create deterministic execution hash
    const executionHash = this.generateHash({
      rules: rulesHash,
      input: inputHash,
      output: outputHash,
      appliedRules: appliedRules.sort() // Sort for determinism
    });

    const execution = {
      executionHash,
      rulesFile: options.rulesFile || 'unknown',
      rulesHash,
      inputHash,
      outputHash,
      appliedRules,
      auditTrail,
      finalState: state,
      executionTime,
      metadata: {
        version: rulesData.metadata?.version || '1.0.0',
        description: rulesData.metadata?.description || '',
        ruleCount: sortedRules.length,
        appliedCount: appliedRules.length,
        timestamp: new Date().toISOString()
      }
    };

    console.log(`🏁 Execution completed in ${executionTime}ms`);
    console.log(`📝 Hash: ${executionHash.substring(0, 12)}`);
    
    return execution;
  }

  // Git-style commit
  async commit(execution, message = '', parentHash = null) {
    await this.initDatabase();
    
    // Get current HEAD if no parent specified
    if (!parentHash) {
      parentHash = await this.getHeadCommit();
    }

    const commitData = {
      execution: execution.executionHash,
      parent: parentHash,
      author: 'logic-git',
      timestamp: new Date().toISOString(),
      message: message || `Execute ${execution.rulesFile}`
    };

    const commitHash = await this.hashObject(commitData, 'commit');
    
    // Store execution in database
    await new Promise((resolve, reject) => {
      this.db.run(`
        INSERT INTO executions 
        (execution_hash, commit_hash, parent_hash, rules_file, rules_hash, 
         input_hash, output_hash, applied_rules, execution_time_ms, branch, message, timestamp)
        VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)
      `, [
        execution.executionHash,
        commitHash,
        parentHash,
        execution.rulesFile,
        execution.rulesHash,
        execution.inputHash,
        execution.outputHash,
        JSON.stringify(execution.appliedRules),
        execution.executionTime,
        this.currentBranch,
        message,
        execution.metadata.timestamp
      ], (err) => err ? reject(err) : resolve());
    });

    // Store audit trail
    for (const entry of execution.auditTrail) {
      await new Promise((resolve, reject) => {
        this.db.run(`
          INSERT INTO audit_trail 
          (execution_hash, rule_name, condition_text, changes_json, state_before, state_after)
          VALUES (?, ?, ?, ?, ?, ?)
        `, [
          execution.executionHash,
          entry.rule,
          entry.condition,
          JSON.stringify(entry.changes),
          JSON.stringify(entry.stateBefore),
          JSON.stringify(entry.stateAfter)
        ], (err) => err ? reject(err) : resolve());
      });
    }

    // Store final state snapshot
    await new Promise((resolve, reject) => {
      this.db.run(`
        INSERT INTO state_snapshots 
        (execution_hash, snapshot_type, state_data, state_hash)
        VALUES (?, ?, ?, ?)
      `, [
        execution.executionHash,
        'final',
        JSON.stringify(execution.finalState),
        execution.outputHash
      ], (err) => err ? reject(err) : resolve());
    });

    // Update HEAD
    await this.updateHead(commitHash);
    
    console.log(`💾 [${commitHash.substring(0, 8)}] ${message}`);
    return commitHash;
  }

  // Execute and commit in one operation
  async execute(rulesFile, dataFile, message = '') {
    try {
      console.log(`\n🎯 Git for Logic - Execute & Commit`);
      console.log(`📋 Rules: ${rulesFile}`);
      console.log(`📊 Data: ${dataFile}`);
      
      const rulesData = this.loadRules(rulesFile);
      const inputData = this.loadData(dataFile);
      
      // Handle array of records or single record
      const records = Array.isArray(inputData) ? inputData : [inputData];
      const results = [];
      
      for (let i = 0; i < records.length; i++) {
        console.log(`\n--- Processing Record ${i + 1}/${records.length} ---`);
        
        const execution = await this.executeRules(rulesData, records[i], { rulesFile });
        const commitMessage = message || `Execute ${rulesFile} on record ${i + 1}`;
        const commitHash = await this.commit(execution, commitMessage);
        
        results.push({
          recordIndex: i,
          commitHash,
          executionHash: execution.executionHash,
          finalState: execution.finalState,
          appliedRules: execution.appliedRules
        });
        
        console.log(`🎯 Final State:`, JSON.stringify(execution.finalState, null, 2));
      }
      
      return results;
      
    } catch (error) {
      console.error('❌ Execution failed:', error.message);
      throw error;
    }
  }

  // Show execution history (like git log)
  async log(limit = 10, branch = null) {
    await this.initDatabase();
    
    const branchFilter = branch || this.currentBranch;
    
    const rows = await new Promise((resolve, reject) => {
      this.db.all(`
        SELECT * FROM executions 
        WHERE branch = ?
        ORDER BY timestamp DESC 
        LIMIT ?
      `, [branchFilter, limit], (err, rows) => {
        err ? reject(err) : resolve(rows);
      });
    });

    console.log(`\n📚 Logic Git History (${branchFilter}):\n`);
    
    if (rows.length === 0) {
      console.log('No executions found.');
      return;
    }

    rows.forEach((exec, i) => {
      const appliedRules = JSON.parse(exec.applied_rules);
      console.log(`commit ${exec.commit_hash.substring(0, 8)}`);
      console.log(`Execution: ${exec.execution_hash.substring(0, 12)}`);
      console.log(`Author: ${exec.author}`);
      console.log(`Date: ${new Date(exec.timestamp).toLocaleString()}`);
      console.log(`\n    ${exec.message}`);
      console.log(`    Rules: ${exec.rules_file} | Applied: ${appliedRules.length} | Time: ${exec.execution_time_ms}ms\n`);
      if (i < rows.length - 1) console.log('---');
    });
  }

  // Compare two executions (like git diff)
  async diff(hash1, hash2) {
    await this.initDatabase();
    
    const [exec1, exec2] = await Promise.all([
      this.getExecution(hash1),
      this.getExecution(hash2)
    ]);

    if (!exec1 || !exec2) {
      console.error('❌ One or both executions not found');
      return;
    }

    console.log(`\n📊 Diff ${hash1.substring(0, 8)}..${hash2.substring(0, 8)}\n`);
    
    const rules1 = JSON.parse(exec1.applied_rules);
    const rules2 = JSON.parse(exec2.applied_rules);
    
    const added = rules2.filter(r => !rules1.includes(r));
    const removed = rules1.filter(r => !rules2.includes(r));
    
    console.log(`Rules Changed: ${exec1.rules_hash !== exec2.rules_hash ? 'YES' : 'NO'}`);
    console.log(`Output Changed: ${exec1.output_hash !== exec2.output_hash ? 'YES' : 'NO'}`);
    console.log(`Time Diff: ${exec2.execution_time_ms - exec1.execution_time_ms}ms`);
    
    if (added.length > 0) {
      console.log(`\n➕ Rules Added:`);
      added.forEach(rule => console.log(`   + ${rule}`));
    }
    
    if (removed.length > 0) {
      console.log(`\n➖ Rules Removed:`);
      removed.forEach(rule => console.log(`   - ${rule}`));
    }
    
    if (added.length === 0 && removed.length === 0) {
      console.log(`\n✨ Same rules applied`);
    }
  }

  // Branch operations
  async createBranch(branchName) {
    const headCommit = await this.getHeadCommit();
    const branchPath = path.join(this.repoPath, '.logicgit', 'refs', 'heads', branchName);
    
    if (fs.existsSync(branchPath)) {
      throw new Error(`Branch ${branchName} already exists`);
    }
    
    fs.writeFileSync(branchPath, (headCommit || '') + '\n');
    console.log(`🌿 Created branch: ${branchName}`);
  }

  async checkout(branchName) {
    const branchPath = path.join(this.repoPath, '.logicgit', 'refs', 'heads', branchName);
    
    if (!fs.existsSync(branchPath)) {
      throw new Error(`Branch ${branchName} not found`);
    }
    
    const headPath = path.join(this.repoPath, '.logicgit', 'HEAD');
    fs.writeFileSync(headPath, `ref: refs/heads/${branchName}\n`);
    this.currentBranch = branchName;
    
    console.log(`🌿 Switched to branch: ${branchName}`);
  }

  async listBranches() {
    const refsDir = path.join(this.repoPath, '.logicgit', 'refs', 'heads');
    const branches = fs.readdirSync(refsDir);
    
    console.log('\n🌿 Branches:');
    branches.forEach(branch => {
      const marker = branch === this.currentBranch ? '* ' : '  ';
      console.log(`${marker}${branch}`);
    });
  }

  // Utility methods
  async getHeadCommit() {
    const headPath = path.join(this.repoPath, '.logicgit', 'HEAD');
    if (!fs.existsSync(headPath)) return null;
    
    const headContent = fs.readFileSync(headPath, 'utf8').trim();
    
    if (headContent.startsWith('ref:')) {
      const refPath = headContent.substring(5).trim();
      const fullRefPath = path.join(this.repoPath, '.logicgit', refPath);
      if (fs.existsSync(fullRefPath)) {
        const content = fs.readFileSync(fullRefPath, 'utf8').trim();
        return content || null;
      }
    }
    
    return headContent || null;
  }

  async updateHead(commitHash) {
    const headPath = path.join(this.repoPath, '.logicgit', 'HEAD');
    const headContent = fs.readFileSync(headPath, 'utf8').trim();
    
    if (headContent.startsWith('ref:')) {
      const refPath = headContent.substring(5).trim();
      const fullRefPath = path.join(this.repoPath, '.logicgit', refPath);
      fs.writeFileSync(fullRefPath, commitHash + '\n');
    } else {
      // Detached HEAD
      fs.writeFileSync(headPath, commitHash + '\n');
    }
  }

  async getExecution(hashPrefix) {
    await this.initDatabase();
    
    return new Promise((resolve, reject) => {
      this.db.get(
        'SELECT * FROM executions WHERE execution_hash LIKE ? OR commit_hash LIKE ? ORDER BY timestamp DESC LIMIT 1',
        [`${hashPrefix}%`, `${hashPrefix}%`],
        (err, row) => err ? reject(err) : resolve(row)
      );
    });
  }

  generateHash(data) {
    const content = typeof data === 'string' ? data : JSON.stringify(data, Object.keys(data).sort());
    return crypto.createHash('sha1').update(content).digest('hex');
  }

  // Export execution data
  async exportExecution(hashPrefix, outputPath = null) {
    const execution = await this.getExecution(hashPrefix);
    if (!execution) {
      throw new Error(`Execution ${hashPrefix} not found`);
    }

    if (!outputPath) {
      outputPath = path.join(this.repoPath, 'exports', `execution_${execution.execution_hash.substring(0, 8)}.json`);
    }

    // Get audit trail
    const auditTrail = await new Promise((resolve, reject) => {
      this.db.all(
        'SELECT * FROM audit_trail WHERE execution_hash = ? ORDER BY timestamp',
        [execution.execution_hash],
        (err, rows) => err ? reject(err) : resolve(rows)
      );
    });

    // Get state snapshot
    const snapshot = await new Promise((resolve, reject) => {
      this.db.get(
        'SELECT * FROM state_snapshots WHERE execution_hash = ? AND snapshot_type = "final"',
        [execution.execution_hash],
        (err, row) => err ? reject(err) : resolve(row)
      );
    });

    const exportData = {
      execution,
      auditTrail,
      finalState: snapshot ? JSON.parse(snapshot.state_data) : null,
      exportTimestamp: new Date().toISOString(),
      exportVersion: '1.0.0'
    };

    fs.writeFileSync(outputPath, JSON.stringify(exportData, null, 2));
    console.log(`📤 Exported to: ${outputPath}`);
    return outputPath;
  }

  async close() {
    if (this.db) {
      await new Promise((resolve) => {
        this.db.close((err) => {
          if (err) console.error('Database close error:', err);
          resolve();
        });
      });
    }
  }
}

// CLI Interface
async function main() {
  const args = process.argv.slice(2);
  const cmd = args[0];

  try {
    const git = new GitForLogic();

    switch (cmd) {
      case 'init':
        console.log('🎯 Initialized Git for Logic repository');
        console.log(`📂 Location: ${git.repoPath}`);
        break;

      case 'execute': {
        const rulesFile = args[1];
        const dataFile = args[2];
        const message = args.slice(3).join(' ') || '';
        
        if (!rulesFile || !dataFile) {
          console.log('Usage: node git-for-logic.js execute <rules.yaml> <data.json|csv> [message]');
          return;
        }
        
        await git.execute(rulesFile, dataFile, message);
        break;
      }

      case 'log': {
        const limit = parseInt(args[1]) || 10;
        const branch = args[2];
        await git.log(limit, branch);
        break;
      }

      case 'diff': {
        const hash1 = args[1];
        const hash2 = args[2];
        
        if (!hash1 || !hash2) {
          console.log('Usage: node git-for-logic.js diff <hash1> <hash2>');
          return;
        }
        
        await git.diff(hash1, hash2);
        break;
      }

      case 'branch': {
        if (args[1]) {
          await git.createBranch(args[1]);
        } else {
          await git.listBranches();
        }
        break;
      }

      case 'checkout': {
        const branchName = args[1];
        if (!branchName) {
          console.log('Usage: node git-for-logic.js checkout <branch>');
          return;
        }
        await git.checkout(branchName);
        break;
      }

      case 'export': {
        const hash = args[1];
        const outputPath = args[2];
        
        if (!hash) {
          console.log('Usage: node git-for-logic.js export <execution-hash> [output-path]');
          return;
        }
        
        await git.exportExecution(hash, outputPath);
        break;
      }

      default:
        console.log(`
🎯 Git for Logic - Version Control for Business Rules

Commands:
  init                                   Initialize repository
  execute <rules.yaml> <data.json> [msg] Execute rules and commit
  log [count] [branch]                   Show execution history
  diff <hash1> <hash2>                   Compare executions
  branch [name]                          List branches or create new
  checkout <branch>                      Switch branches
  export <hash> [path]                   Export execution data

Examples:
  node git-for-logic.js init
  node git-for-logic.js execute loan-rules.yaml applicants.csv "Risk assessment v2"
  node git-for-logic.js log 5
  node git-for-logic.js diff a1b2c3 d4e5f6
  node git-for-logic.js branch experiment
  node git-for-logic.js checkout experiment
  node git-for-logic.js export a1b2c3d4 ./backup.json

Repository Structure:
  logic-repo/
  ├── .logicgit/          # Version control data
  ├── rules/              # YAML rule files
  ├── data/               # Input data (JSON/CSV)
  └── exports/            # Exported executions
        `);
    }

    await git.close();

  } catch (error) {
    console.error('❌ Error:', error.message);
    process.exit(1);
  }
}

if (require.main === module) {
  main();
}

module.exports = GitForLogic;
