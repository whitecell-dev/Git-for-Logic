# Git for Logic 🎯

**Content-addressed version control for business logic execution**

Git for Logic brings Git's powerful versioning model to business rules and decision logic. Instead of versioning code, you version **behavior** - tracking how rules transform inputs into outputs with full reproducibility and audit trails.

## 🚀 Quick Start

### Installation

```bash
# Clone or download the git-for-logic.js file
npm install js-yaml sqlite3  # Required dependencies

# Initialize a new repository
node git-for-logic.js init
```

### Basic Workflow

```bash
# 1. Create some rules (see examples below)
# 2. Prepare your data
# 3. Execute and commit
node git-for-logic.js execute loan-rules.yaml applicants.csv "Initial risk assessment"

# 4. View history
node git-for-logic.js log

# 5. Compare executions
node git-for-logic.js diff a1b2c3 d4e5f6
```

## 📁 Repository Structure

```
logic-repo/
├── .logicgit/           # Version control metadata (like .git)
│   ├── objects/         # Content-addressed object storage
│   ├── refs/heads/      # Branch references
│   ├── HEAD             # Current branch pointer
│   └── state.db         # SQLite database for querying
├── rules/               # YAML rule definitions
├── data/                # Input data (JSON/CSV)
└── exports/             # Exported execution data
```

## 🧠 Core Concepts

### Content Addressing
Every execution is identified by a SHA hash of its:
- Input data
- Rule definitions  
- Output state
- Applied rules

**Same inputs + same rules = same hash** (deterministic execution)

### Git-Style Operations
- **commit**: Store an execution with full audit trail
- **log**: View execution history
- **diff**: Compare two executions
- **branch**: Create parallel rule experiments
- **checkout**: Switch between rule versions

### Audit Trail (MNEME)
Every rule application is logged:
- Which rule fired
- What condition was evaluated
- What changes were made
- Before/after state snapshots

## 📝 Rule Format

Create YAML files in the `rules/` directory:

```yaml
# rules/loan-approval.yaml
metadata:
  name: "Loan Approval Rules"
  version: "1.2.0"
  description: "Risk assessment for loan applications"

rules:
  - name: "high_income_approval"
    priority: 1
    when: "income > 100000 && credit_score > 750"
    then:
      status: "approved"
      approval_amount: "income * 5"
      reason: "High income, excellent credit"

  - name: "standard_approval"
    priority: 2  
    when: "income > 50000 && credit_score > 650"
    then:
      status: "approved"
      approval_amount: "income * 3"
      reason: "Standard approval criteria met"

  - name: "rejection"
    priority: 999
    when: "credit_score < 600"
    then:
      status: "rejected"
      reason: "Credit score too low"
```

## 📊 Data Format

### JSON Input
```json
// data/applicant.json
{
  "name": "John Doe",
  "income": 75000,
  "credit_score": 720,
  "employment_years": 3
}
```

### CSV Input
```csv
// data/applicants.csv
name,income,credit_score,employment_years
John Doe,75000,720,3
Jane Smith,120000,780,5
Bob Wilson,45000,580,2
```

## 🛠 CLI Commands

### Initialize Repository
```bash
node git-for-logic.js init
```

### Execute Rules
```bash
# Single record
node git-for-logic.js execute loan-rules.yaml applicant.json "Test new rules"

# Multiple records (CSV)
node git-for-logic.js execute loan-rules.yaml applicants.csv "Batch processing"
```

### View History
```bash
# Show last 10 executions
node git-for-logic.js log

# Show last 20 executions
node git-for-logic.js log 20

# Show executions from specific branch
node git-for-logic.js log 10 experiment
```

### Compare Executions
```bash
# Compare by execution hash
node git-for-logic.js diff a1b2c3d4 e5f6g7h8

# Shows:
# - Which rules changed
# - Whether output changed
# - Performance differences
```

### Branch Operations
```bash
# List branches
node git-for-logic.js branch

# Create new branch
node git-for-logic.js branch experiment-v2

# Switch branches  
node git-for-logic.js checkout experiment-v2
```

### Export Data
```bash
# Export execution for analysis
node git-for-logic.js export a1b2c3d4 ./analysis.json

# Includes:
# - Full execution details
# - Audit trail
# - Final state
# - Metadata
```

## 🔧 Integration Example

```javascript
const GitForLogic = require('./git-for-logic.js');

async function processApplications() {
  const git = new GitForLogic('./my-logic-repo');
  
  // Execute rules
  const results = await git.execute(
    'loan-approval.yaml',
    'applications.csv', 
    'Daily batch processing'
  );
  
  // Each result contains:
  results.forEach(result => {
    console.log(`Commit: ${result.commitHash}`);
    console.log(`Status: ${result.finalState.status}`);
    console.log(`Rules applied: ${result.appliedRules.join(', ')}`);
  });
  
  await git.close();
}
```

## 🧪 Example Workflow

### 1. Initialize and Setup
```bash
mkdir my-rules-project
cd my-rules-project
node git-for-logic.js init
```

### 2. Create Rules
```bash
# Create rules/simple-approval.yaml
cat > rules/simple-approval.yaml << 'EOF'
metadata:
  name: "Simple Approval"
  version: "1.0.0"

rules:
  - name: "auto_approve"
    priority: 1
    when: "score > 80"
    then:
      status: "approved"
      
  - name: "auto_reject" 
    priority: 2
    when: "score < 50"
    then:
      status: "rejected"
      
  - name: "manual_review"
    priority: 3
    when: "true"
    then:
      status: "review"
EOF
```

### 3. Create Test Data
```bash
# Create data/test-cases.json
cat > data/test-cases.json << 'EOF'
[
  {"name": "Alice", "score": 85},
  {"name": "Bob", "score": 45},
  {"name": "Charlie", "score": 65}
]
EOF
```

### 4. Execute and Commit
```bash
node git-for-logic.js execute simple-approval.yaml test-cases.json "Initial test run"
```

### 5. View Results
```bash
node git-for-logic.js log
```

## 🔍 Understanding the Output

### Execution Hash
```
🏁 Execution completed in 15ms
📝 Hash: a1b2c3d4e5f6
```
- **Deterministic**: Same inputs/rules always produce same hash
- **Collision-resistant**: Different executions have different hashes
- **Auditable**: Hash proves execution integrity

### Commit Log
```
commit a1b2c3d4
Execution: a1b2c3d4e5f6
Author: logic-git
Date: 2024-01-15 10:30:45

    Initial test run
    Rules: simple-approval.yaml | Applied: 3 | Time: 15ms
```

### Diff Output
```
📊 Diff a1b2c3d4..e5f6g7h8

Rules Changed: NO
Output Changed: YES
Time Diff: +5ms

✨ Same rules applied
```

## 🏗 Architecture

### Git Internals Applied to Logic
| Git Concept | Logic Equivalent | Purpose |
|-------------|------------------|---------|
| **blob** | State snapshot | Store input/output data |
| **tree** | Rule dependencies | Track rule relationships |
| **commit** | Execution record | Link rules + data + results |
| **branch** | Rule experiments | Parallel rule development |

### Storage Layers
1. **SQLite Database**: Fast querying and analysis
2. **Filesystem Objects**: Git-compatible content addressing
3. **Audit Trail**: Complete execution provenance

### Deterministic Execution
- Rules sorted by priority
- Conditions evaluated safely
- State mutations tracked
- Hash includes execution order

## 🚦 Best Practices

### Rule Design
- Use clear, descriptive rule names
- Set explicit priorities (lower = higher priority)
- Write simple, testable conditions
- Document rule purpose in metadata

### Data Management
- Use consistent field naming
- Validate input data schemas
- Keep test cases in version control
- Export important executions

### Branching Strategy
- `main`: Production rules
- `experiment-*`: New rule testing
- `hotfix-*`: Critical rule fixes
- `feature-*`: Rule enhancements

### Performance
- Batch similar inputs together
- Use CSV for large datasets
- Monitor execution times
- Export and analyze patterns

## 🔬 Advanced Features

### Custom Condition Logic
```yaml
rules:
  - name: "complex_condition"
    when: "(income > 50000 && debt_ratio < 0.3) || (assets > 200000)"
    then:
      status: "approved"
```

### Nested State Updates
```yaml
rules:
  - name: "set_nested_values"
    when: "status == 'approved'"
    then:
      loan.amount: "income * 4"
      loan.rate: "0.035"
      loan.term: "30"
```

### Rule Metadata
```yaml
metadata:
  name: "Credit Decision Engine"
  version: "2.1.0"
  author: "Risk Team"
  description: "Automated credit approval with manual review fallback"
  domain: "financial_services"
```

## 🐛 Troubleshooting

### Common Issues

**"Rules file not found"**
- Check file path relative to repository root
- Ensure file is in `rules/` directory

**"Condition evaluation failed"**  
- Use simple JavaScript expressions
- Reference data fields correctly (e.g., `income > 50000`)
- Avoid complex nested expressions

**"Database locked"**
- Close previous GitForLogic instances
- Check for zombie processes

### Debug Mode
```javascript
// Enable detailed logging
const git = new GitForLogic('./repo');
git.debug = true;
```

## 🤝 Contributing

This is a proof-of-concept implementation. Contributions welcome:

1. Enhanced condition evaluation
2. Rule dependency analysis  
3. Visual diff tools
4. Performance optimizations
5. Integration examples

## 📄 License

MIT License - Build something awesome!

---

**Git for Logic** - Where business rules meet version control 🎯
