/* ====================================================================== */
/* CALYX C BUNDLE - LLM OPTIMIZED FORMAT */
/* ====================================================================== */

/* METADATA SECTION */
const char* CALYX_METADATA = {
  "format_version": "calyx-c-1.0",
  "total_files": 3,
  "total_headers": 1,
  "layers": {
    "UTILITY": 3
  },
  "external_includes": [
    "openssl/sha.h",
    "stdarg.h",
    "stdbool.h",
    "stddef.h",
    "stdint.h",
    "stdio.h",
    "stdlib.h",
    "string.h",
    "sys/stat.h",
    "time.h"
  ],
  "generated_at": "2026-01-03T06:47:57.291333Z"
};

/* ====================================================================== */
/* FILE MAP (name → metadata) */
/* ====================================================================== */
/* FILE_MAP structure would be defined here */
/* In C, we'd use an array of structs or similar */

/*
FILE MAP:
  git_for_logic.h:
    layer: UTILITY
    functions: []
    defines: ['GIT_FOR_LOGIC_H']
  git_for_logic.c:
    layer: UTILITY
    functions: ['compute_sha1', 'ensure_directory', 'repo_init', 'repo_execute', 'repo_close', 'main']
    defines: ['_POSIX_C_SOURCE', '_GNU_SOURCE', 'MAX_PATH_LEN', 'HASH_HEX_LEN']
    header: git_for_logic.h
  sqlite3.h:
    layer: UTILITY
    functions: []
    defines: ['_SQLITE3_H_', 'SQLITE_EXTERN', 'SQLITE_API', 'SQLITE_DEPRECATED', 'SQLITE_EXPERIMENTAL', 'SQLITE_VERSION', 'SQLITE_VERSION_NUMBER', 'SQLITE_SOURCE_ID', 'double', 'SQLITE_OK', 'SQLITE_ERROR', 'SQLITE_INTERNAL', 'SQLITE_PERM', 'SQLITE_ABORT', 'SQLITE_BUSY', 'SQLITE_LOCKED', 'SQLITE_NOMEM', 'SQLITE_READONLY', 'SQLITE_INTERRUPT', 'SQLITE_IOERR', 'SQLITE_CORRUPT', 'SQLITE_NOTFOUND', 'SQLITE_FULL', 'SQLITE_CANTOPEN', 'SQLITE_PROTOCOL', 'SQLITE_EMPTY', 'SQLITE_SCHEMA', 'SQLITE_TOOBIG', 'SQLITE_CONSTRAINT', 'SQLITE_MISMATCH', 'SQLITE_MISUSE', 'SQLITE_NOLFS', 'SQLITE_AUTH', 'SQLITE_FORMAT', 'SQLITE_RANGE', 'SQLITE_NOTADB', 'SQLITE_ROW', 'SQLITE_DONE', 'SQLITE_IOERR_READ', 'SQLITE_IOERR_SHORT_READ', 'SQLITE_IOERR_WRITE', 'SQLITE_IOERR_FSYNC', 'SQLITE_IOERR_DIR_FSYNC', 'SQLITE_IOERR_TRUNCATE', 'SQLITE_IOERR_FSTAT', 'SQLITE_IOERR_UNLOCK', 'SQLITE_IOERR_RDLOCK', 'SQLITE_IOERR_DELETE', 'SQLITE_IOERR_BLOCKED', 'SQLITE_IOERR_NOMEM', 'SQLITE_IOERR_ACCESS', 'SQLITE_IOERR_CHECKRESERVEDLOCK', 'SQLITE_IOERR_LOCK', 'SQLITE_IOERR_CLOSE', 'SQLITE_IOERR_DIR_CLOSE', 'SQLITE_IOERR_SHMOPEN', 'SQLITE_IOERR_SHMSIZE', 'SQLITE_IOERR_SHMLOCK', 'SQLITE_IOERR_SHMMAP', 'SQLITE_IOERR_SEEK', 'SQLITE_LOCKED_SHAREDCACHE', 'SQLITE_BUSY_RECOVERY', 'SQLITE_CANTOPEN_NOTEMPDIR', 'SQLITE_CORRUPT_VTAB', 'SQLITE_READONLY_RECOVERY', 'SQLITE_READONLY_CANTLOCK', 'SQLITE_OPEN_READONLY', 'SQLITE_OPEN_READWRITE', 'SQLITE_OPEN_CREATE', 'SQLITE_OPEN_DELETEONCLOSE', 'SQLITE_OPEN_EXCLUSIVE', 'SQLITE_OPEN_AUTOPROXY', 'SQLITE_OPEN_URI', 'SQLITE_OPEN_MAIN_DB', 'SQLITE_OPEN_TEMP_DB', 'SQLITE_OPEN_TRANSIENT_DB', 'SQLITE_OPEN_MAIN_JOURNAL', 'SQLITE_OPEN_TEMP_JOURNAL', 'SQLITE_OPEN_SUBJOURNAL', 'SQLITE_OPEN_MASTER_JOURNAL', 'SQLITE_OPEN_NOMUTEX', 'SQLITE_OPEN_FULLMUTEX', 'SQLITE_OPEN_SHAREDCACHE', 'SQLITE_OPEN_PRIVATECACHE', 'SQLITE_OPEN_WAL', 'SQLITE_IOCAP_ATOMIC', 'SQLITE_IOCAP_ATOMIC512', 'SQLITE_IOCAP_ATOMIC1K', 'SQLITE_IOCAP_ATOMIC2K', 'SQLITE_IOCAP_ATOMIC4K', 'SQLITE_IOCAP_ATOMIC8K', 'SQLITE_IOCAP_ATOMIC16K', 'SQLITE_IOCAP_ATOMIC32K', 'SQLITE_IOCAP_ATOMIC64K', 'SQLITE_IOCAP_SAFE_APPEND', 'SQLITE_IOCAP_SEQUENTIAL', 'SQLITE_IOCAP_UNDELETABLE_WHEN_OPEN', 'SQLITE_LOCK_NONE', 'SQLITE_LOCK_SHARED', 'SQLITE_LOCK_RESERVED', 'SQLITE_LOCK_PENDING', 'SQLITE_LOCK_EXCLUSIVE', 'SQLITE_SYNC_NORMAL', 'SQLITE_SYNC_FULL', 'SQLITE_SYNC_DATAONLY', 'SQLITE_FCNTL_LOCKSTATE', 'SQLITE_GET_LOCKPROXYFILE', 'SQLITE_SET_LOCKPROXYFILE', 'SQLITE_LAST_ERRNO', 'SQLITE_FCNTL_SIZE_HINT', 'SQLITE_FCNTL_CHUNK_SIZE', 'SQLITE_FCNTL_FILE_POINTER', 'SQLITE_FCNTL_SYNC_OMITTED', 'SQLITE_ACCESS_EXISTS', 'SQLITE_ACCESS_READWRITE', 'SQLITE_ACCESS_READ', 'SQLITE_SHM_UNLOCK', 'SQLITE_SHM_LOCK', 'SQLITE_SHM_SHARED', 'SQLITE_SHM_EXCLUSIVE', 'SQLITE_SHM_NLOCK', 'SQLITE_CONFIG_SINGLETHREAD', 'SQLITE_CONFIG_MULTITHREAD', 'SQLITE_CONFIG_SERIALIZED', 'SQLITE_CONFIG_MALLOC', 'SQLITE_CONFIG_GETMALLOC', 'SQLITE_CONFIG_SCRATCH', 'SQLITE_CONFIG_PAGECACHE', 'SQLITE_CONFIG_HEAP', 'SQLITE_CONFIG_MEMSTATUS', 'SQLITE_CONFIG_MUTEX', 'SQLITE_CONFIG_GETMUTEX', 'SQLITE_CONFIG_LOOKASIDE', 'SQLITE_CONFIG_PCACHE', 'SQLITE_CONFIG_GETPCACHE', 'SQLITE_CONFIG_LOG', 'SQLITE_CONFIG_URI', 'SQLITE_DBCONFIG_LOOKASIDE', 'SQLITE_DBCONFIG_ENABLE_FKEY', 'SQLITE_DBCONFIG_ENABLE_TRIGGER', 'SQLITE_DENY', 'SQLITE_IGNORE', 'SQLITE_CREATE_INDEX', 'SQLITE_CREATE_TABLE', 'SQLITE_CREATE_TEMP_INDEX', 'SQLITE_CREATE_TEMP_TABLE', 'SQLITE_CREATE_TEMP_TRIGGER', 'SQLITE_CREATE_TEMP_VIEW', 'SQLITE_CREATE_TRIGGER', 'SQLITE_CREATE_VIEW', 'SQLITE_DELETE', 'SQLITE_DROP_INDEX', 'SQLITE_DROP_TABLE', 'SQLITE_DROP_TEMP_INDEX', 'SQLITE_DROP_TEMP_TABLE', 'SQLITE_DROP_TEMP_TRIGGER', 'SQLITE_DROP_TEMP_VIEW', 'SQLITE_DROP_TRIGGER', 'SQLITE_DROP_VIEW', 'SQLITE_INSERT', 'SQLITE_PRAGMA', 'SQLITE_READ', 'SQLITE_SELECT', 'SQLITE_TRANSACTION', 'SQLITE_UPDATE', 'SQLITE_ATTACH', 'SQLITE_DETACH', 'SQLITE_ALTER_TABLE', 'SQLITE_REINDEX', 'SQLITE_ANALYZE', 'SQLITE_CREATE_VTABLE', 'SQLITE_DROP_VTABLE', 'SQLITE_FUNCTION', 'SQLITE_SAVEPOINT', 'SQLITE_COPY', 'SQLITE_LIMIT_LENGTH', 'SQLITE_LIMIT_SQL_LENGTH', 'SQLITE_LIMIT_COLUMN', 'SQLITE_LIMIT_EXPR_DEPTH', 'SQLITE_LIMIT_COMPOUND_SELECT', 'SQLITE_LIMIT_VDBE_OP', 'SQLITE_LIMIT_FUNCTION_ARG', 'SQLITE_LIMIT_ATTACHED', 'SQLITE_LIMIT_LIKE_PATTERN_LENGTH', 'SQLITE_LIMIT_VARIABLE_NUMBER', 'SQLITE_LIMIT_TRIGGER_DEPTH', 'SQLITE_INTEGER', 'SQLITE_FLOAT', 'SQLITE_BLOB', 'SQLITE_NULL', 'SQLITE_TEXT', 'SQLITE3_TEXT', 'SQLITE_UTF8', 'SQLITE_UTF16LE', 'SQLITE_UTF16BE', 'SQLITE_UTF16', 'SQLITE_ANY', 'SQLITE_UTF16_ALIGNED', 'SQLITE_STATIC', 'SQLITE_TRANSIENT', 'SQLITE_INDEX_CONSTRAINT_EQ', 'SQLITE_INDEX_CONSTRAINT_GT', 'SQLITE_INDEX_CONSTRAINT_LE', 'SQLITE_INDEX_CONSTRAINT_LT', 'SQLITE_INDEX_CONSTRAINT_GE', 'SQLITE_INDEX_CONSTRAINT_MATCH', 'SQLITE_MUTEX_FAST', 'SQLITE_MUTEX_RECURSIVE', 'SQLITE_MUTEX_STATIC_MASTER', 'SQLITE_MUTEX_STATIC_MEM', 'SQLITE_MUTEX_STATIC_MEM2', 'SQLITE_MUTEX_STATIC_OPEN', 'SQLITE_MUTEX_STATIC_PRNG', 'SQLITE_MUTEX_STATIC_LRU', 'SQLITE_MUTEX_STATIC_LRU2', 'SQLITE_MUTEX_STATIC_PMEM', 'SQLITE_TESTCTRL_FIRST', 'SQLITE_TESTCTRL_PRNG_SAVE', 'SQLITE_TESTCTRL_PRNG_RESTORE', 'SQLITE_TESTCTRL_PRNG_RESET', 'SQLITE_TESTCTRL_BITVEC_TEST', 'SQLITE_TESTCTRL_FAULT_INSTALL', 'SQLITE_TESTCTRL_BENIGN_MALLOC_HOOKS', 'SQLITE_TESTCTRL_PENDING_BYTE', 'SQLITE_TESTCTRL_ASSERT', 'SQLITE_TESTCTRL_ALWAYS', 'SQLITE_TESTCTRL_RESERVE', 'SQLITE_TESTCTRL_OPTIMIZATIONS', 'SQLITE_TESTCTRL_ISKEYWORD', 'SQLITE_TESTCTRL_PGHDRSZ', 'SQLITE_TESTCTRL_SCRATCHMALLOC', 'SQLITE_TESTCTRL_LOCALTIME_FAULT', 'SQLITE_TESTCTRL_LAST', 'SQLITE_STATUS_MEMORY_USED', 'SQLITE_STATUS_PAGECACHE_USED', 'SQLITE_STATUS_PAGECACHE_OVERFLOW', 'SQLITE_STATUS_SCRATCH_USED', 'SQLITE_STATUS_SCRATCH_OVERFLOW', 'SQLITE_STATUS_MALLOC_SIZE', 'SQLITE_STATUS_PARSER_STACK', 'SQLITE_STATUS_PAGECACHE_SIZE', 'SQLITE_STATUS_SCRATCH_SIZE', 'SQLITE_STATUS_MALLOC_COUNT', 'SQLITE_DBSTATUS_LOOKASIDE_USED', 'SQLITE_DBSTATUS_CACHE_USED', 'SQLITE_DBSTATUS_SCHEMA_USED', 'SQLITE_DBSTATUS_STMT_USED', 'SQLITE_DBSTATUS_LOOKASIDE_HIT', 'SQLITE_DBSTATUS_LOOKASIDE_MISS_SIZE', 'SQLITE_DBSTATUS_LOOKASIDE_MISS_FULL', 'SQLITE_DBSTATUS_MAX', 'SQLITE_STMTSTATUS_FULLSCAN_STEP', 'SQLITE_STMTSTATUS_SORT', 'SQLITE_STMTSTATUS_AUTOINDEX', 'SQLITE_CHECKPOINT_PASSIVE', 'SQLITE_CHECKPOINT_FULL', 'SQLITE_CHECKPOINT_RESTART', 'SQLITE_VTAB_CONSTRAINT_SUPPORT', 'SQLITE_ROLLBACK', 'SQLITE_FAIL', 'SQLITE_REPLACE', '_SQLITE3RTREE_H_']
*/

/* ====================================================================== */
/* DEPENDENCY GRAPH (file → [dependencies]) */
/* ====================================================================== */
/*
DEPENDENCY GRAPH:
  git_for_logic.c: ['git_for_logic.h']
  git_for_logic.h: []
  sqlite3.h: []
*/

/* ====================================================================== */
/* FILE CONTENTS (PRESERVED EXACTLY) */
/* ====================================================================== */

/* HEADER FILES */
/* ------------------------------------------------------------ */
/* HEADER: git_for_logic.h */
/* ------------------------------------------------------------ */
#ifndef GIT_FOR_LOGIC_H
#define GIT_FOR_LOGIC_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

typedef struct repo_t repo_t;
typedef struct rules_file_t rules_file_t;
typedef struct execution_t execution_t;

typedef enum {
    ERR_OK = 0,
    ERR_MALLOC_FAILED = 1,
    ERR_FILE_NOT_FOUND = 2,
    ERR_IO = 3,
    ERR_INVALID_YAML = 4,
    ERR_INVALID_JSON = 5,
    ERR_DB_ERROR = 6,
    ERR_HASH_COLLISION = 7,
    ERR_BUFFER_OVERFLOW = 8,
    ERR_DIV_ZERO = 9,
    ERR_NULL_PTR = 10,
    ERR_BRANCH_EXISTS = 11,
    ERR_BRANCH_NOT_FOUND = 12,
} error_t;

error_t repo_init(const char* path, repo_t** out_repo);
error_t repo_execute(repo_t* repo, const char* rules_file, const char* data_file, const char* message);
void repo_close(repo_t* repo);
const char* error_string(error_t err);

#endif


/* SOURCE FILES */
/* ------------------------------------------------------------ */
/* FILE: git_for_logic.c */
/* LAYER: UTILITY */
/* PATH: git_for_logic.c */
/* ------------------------------------------------------------ */
#define _POSIX_C_SOURCE 200809L  // For popen/pclose
#define _GNU_SOURCE               // For feature flags

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <time.h>
#include <sys/stat.h>
#include <openssl/sha.h>
#include "git_for_logic.h"

#define MAX_PATH_LEN 4096
#define HASH_HEX_LEN 40

typedef char hash_t[41];

// ACTUAL STRUCT DEFINITION (matches forward declaration)
struct repo_t {
    char repo_path[MAX_PATH_LEN];
    char db_path[MAX_PATH_LEN];
    void* db;  // sqlite3* but we're avoiding the dependency
    char current_branch[256];
};

static error_t compute_sha1(const char* data, size_t len, hash_t out_hash) {
    unsigned char hash[SHA_DIGEST_LENGTH];
    SHA1((const unsigned char*)data, len, hash);
    for (int i = 0; i < SHA_DIGEST_LENGTH; i++) {
        snprintf(&out_hash[i * 2], 3, "%02x", hash[i]);
    }
    out_hash[HASH_HEX_LEN] = '\0';
    return ERR_OK;
}

static error_t ensure_directory(const char* path) {
    struct stat st;
    if (stat(path, &st) == 0) return ERR_OK;
#ifdef _WIN32
    if (mkdir(path) != 0) return ERR_IO;
#else
    if (mkdir(path, 0755) != 0) return ERR_IO;
#endif
    return ERR_OK;
}

error_t repo_init(const char* path, repo_t** out_repo) {
    if (!path || !out_repo) return ERR_NULL_PTR;
    
    repo_t* repo = (repo_t*)calloc(1, sizeof(repo_t));
    if (!repo) return ERR_MALLOC_FAILED;
    
    strncpy(repo->repo_path, path, MAX_PATH_LEN - 1);
    snprintf(repo->db_path, MAX_PATH_LEN, "%s/.logicgit/state.db", path);
    strncpy(repo->current_branch, "main", sizeof(repo->current_branch) - 1);
    
    char dir[MAX_PATH_LEN];
    
    snprintf(dir, sizeof(dir), "%s/.logicgit", path);
    ensure_directory(dir);
    
    snprintf(dir, sizeof(dir), "%s/.logicgit/objects", path);
    ensure_directory(dir);
    
    snprintf(dir, sizeof(dir), "%s/.logicgit/refs/heads", path);
    ensure_directory(dir);
    
    snprintf(dir, sizeof(dir), "%s/rules", path);
    ensure_directory(dir);
    
    snprintf(dir, sizeof(dir), "%s/data", path);
    ensure_directory(dir);
    
    snprintf(dir, sizeof(dir), "%s/.logicgit/HEAD", path);
    FILE* f = fopen(dir, "wx");
    if (f) {
        fprintf(f, "ref: refs/heads/main\n");
        fclose(f);
    }
    
    *out_repo = repo;
    printf("🎯 Initialized Git for Logic repository\n");
    printf("📂 Location: %s\n", path);
    return ERR_OK;
}

static char* read_file_content(const char* filepath) {
    FILE* f = fopen(filepath, "r");
    if (!f) return NULL;

    if (fseek(f, 0, SEEK_END) != 0) {
        fclose(f);
        return NULL;
    }

    long size = ftell(f);
    if (size < 0) {
        fclose(f);
        return NULL;
    }

    if (fseek(f, 0, SEEK_SET) != 0) {
        fclose(f);
        return NULL;
    }

    char* content = (char*)malloc((size_t)size + 1);
    if (!content) {
        fclose(f);
        return NULL;
    }

    size_t read_bytes = fread(content, 1, (size_t)size, f);
    if (read_bytes != (size_t)size) {
        fclose(f);
        free(content);
        return NULL;
    }

    content[size] = '\0';
    fclose(f);
    return content;
}


error_t repo_execute(repo_t* repo, const char* rules_file, const char* data_file, const char* message) {
    if (!repo || !rules_file || !data_file) return ERR_NULL_PTR;
    
    printf("\n🎯 Git for Logic - Execute & Commit\n");
    printf("📋 Rules: %s\n", rules_file);
    printf("📊 Data: %s\n", data_file);
    
    // Build file paths
    char rules_path[MAX_PATH_LEN];
    char data_path[MAX_PATH_LEN];
    
    int written = snprintf(rules_path, sizeof(rules_path), "%s/rules/%s", repo->repo_path, rules_file);
    if (written < 0 || (size_t)written >= sizeof(rules_path)) return ERR_BUFFER_OVERFLOW;

    written = snprintf(data_path, sizeof(data_path), "%s/data/%s", repo->repo_path, data_file);
    if (written < 0 || (size_t)written >= sizeof(data_path)) return ERR_BUFFER_OVERFLOW;

       
    // Read files
    char* rules_content = read_file_content(rules_path);
    if (!rules_content) return ERR_FILE_NOT_FOUND;
    
    char* data_content = read_file_content(data_path);
    if (!data_content) {
        free(rules_content);
        return ERR_FILE_NOT_FOUND;
    }
    
    // Compute hashes
    hash_t rules_hash, data_hash, exec_hash;
    
    compute_sha1(rules_content, strlen(rules_content), rules_hash);
    compute_sha1(data_content, strlen(data_content), data_hash);
    
    char exec_data[1024];
    snprintf(exec_data, sizeof(exec_data), "rules:%s data:%s", rules_hash, data_hash);
    compute_sha1(exec_data, strlen(exec_data), exec_hash);
    
    printf("💾 Execution hash: %.12s\n", exec_hash);
    printf("📝 Message: %s\n", message ? message : "(no message)");
    printf("📏 Rules size: %zu bytes\n", strlen(rules_content));
    printf("📏 Data size: %zu bytes\n", strlen(data_content));
    
    free(rules_content);
    free(data_content);
    
    return ERR_OK;
}

void repo_close(repo_t* repo) {
    if (!repo) return;
    // If we had a real DB: if (repo->db) sqlite3_close(repo->db);
    free(repo);
}

const char* error_string(error_t err) {
    switch (err) {
        case ERR_OK: return "Success";
        case ERR_MALLOC_FAILED: return "Memory allocation failed";
        case ERR_FILE_NOT_FOUND: return "File not found";
        case ERR_IO: return "I/O error";
        case ERR_INVALID_YAML: return "Invalid YAML";
        case ERR_INVALID_JSON: return "Invalid JSON";
        case ERR_DB_ERROR: return "Database error";
        default: return "Unknown error";
    }
}

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("Usage: %s <command>\n", argv[0]);
        printf("Commands:\n");
        printf("  init                             Initialize repository\n");
        printf("  execute <rules> <data> [message] Execute rules and commit\n");
        return 1;
    }
    
    if (strcmp(argv[1], "init") == 0) {
        repo_t* repo = NULL;
        error_t err = repo_init(".", &repo);
        if (err != ERR_OK) {
            fprintf(stderr, "Error: %s\n", error_string(err));
            return 1;
        }
        repo_close(repo);
        return 0;
    }
    
    if (strcmp(argv[1], "execute") == 0) {
        if (argc < 4) {
            fprintf(stderr, "Usage: %s execute <rules> <data> [message]\n", argv[0]);
            return 1;
        }
        
        const char* rules_file = argv[2];
        const char* data_file = argv[3];
        const char* message = argc > 4 ? argv[4] : "Execute rules";
        
        repo_t* repo = NULL;
        error_t err = repo_init("./logic-repo", &repo);
        if (err != ERR_OK) {
            fprintf(stderr, "Error: %s\n", error_string(err));
            return 1;
        }
        
        err = repo_execute(repo, rules_file, data_file, message);
        repo_close(repo);
        
        if (err != ERR_OK) {
            fprintf(stderr, "Error: %s\n", error_string(err));
            return 1;
        }
        return 0;
    }
    
    fprintf(stderr, "Unknown command: %s\n", argv[1]);
    return 1;
}


/* ====================================================================== */
/* PUBLIC API SUMMARY */
/* ====================================================================== */
/*
AVAILABLE FUNCTIONS BY MODULE:
  git_for_logic.c:
    - compute_sha1
    - ensure_directory
    - repo_init
    - repo_execute
    - repo_close
    - main

DEFINED MACROS:
  - GIT_FOR_LOGIC_H
  - HASH_HEX_LEN
  - MAX_PATH_LEN
  - SQLITE3_TEXT
  - SQLITE_ABORT
  - SQLITE_ACCESS_EXISTS
  - SQLITE_ACCESS_READ
  - SQLITE_ACCESS_READWRITE
  - SQLITE_ALTER_TABLE
  - SQLITE_ANALYZE
  - SQLITE_ANY
  - SQLITE_API
  - SQLITE_ATTACH
  - SQLITE_AUTH
  - SQLITE_BLOB
  - SQLITE_BUSY
  - SQLITE_BUSY_RECOVERY
  - SQLITE_CANTOPEN
  - SQLITE_CANTOPEN_NOTEMPDIR
  - SQLITE_CHECKPOINT_FULL
  - SQLITE_CHECKPOINT_PASSIVE
  - SQLITE_CHECKPOINT_RESTART
  - SQLITE_CONFIG_GETMALLOC
  - SQLITE_CONFIG_GETMUTEX
  - SQLITE_CONFIG_GETPCACHE
  - SQLITE_CONFIG_HEAP
  - SQLITE_CONFIG_LOG
  - SQLITE_CONFIG_LOOKASIDE
  - SQLITE_CONFIG_MALLOC
  - SQLITE_CONFIG_MEMSTATUS
  - SQLITE_CONFIG_MULTITHREAD
  - SQLITE_CONFIG_MUTEX
  - SQLITE_CONFIG_PAGECACHE
  - SQLITE_CONFIG_PCACHE
  - SQLITE_CONFIG_SCRATCH
  - SQLITE_CONFIG_SERIALIZED
  - SQLITE_CONFIG_SINGLETHREAD
  - SQLITE_CONFIG_URI
  - SQLITE_CONSTRAINT
  - SQLITE_COPY
  - SQLITE_CORRUPT
  - SQLITE_CORRUPT_VTAB
  - SQLITE_CREATE_INDEX
  - SQLITE_CREATE_TABLE
  - SQLITE_CREATE_TEMP_INDEX
  - SQLITE_CREATE_TEMP_TABLE
  - SQLITE_CREATE_TEMP_TRIGGER
  - SQLITE_CREATE_TEMP_VIEW
  - SQLITE_CREATE_TRIGGER
  - SQLITE_CREATE_VIEW
  - SQLITE_CREATE_VTABLE
  - SQLITE_DBCONFIG_ENABLE_FKEY
  - SQLITE_DBCONFIG_ENABLE_TRIGGER
  - SQLITE_DBCONFIG_LOOKASIDE
  - SQLITE_DBSTATUS_CACHE_USED
  - SQLITE_DBSTATUS_LOOKASIDE_HIT
  - SQLITE_DBSTATUS_LOOKASIDE_MISS_FULL
  - SQLITE_DBSTATUS_LOOKASIDE_MISS_SIZE
  - SQLITE_DBSTATUS_LOOKASIDE_USED
  - SQLITE_DBSTATUS_MAX
  - SQLITE_DBSTATUS_SCHEMA_USED
  - SQLITE_DBSTATUS_STMT_USED
  - SQLITE_DELETE
  - SQLITE_DENY
  - SQLITE_DEPRECATED
  - SQLITE_DETACH
  - SQLITE_DONE
  - SQLITE_DROP_INDEX
  - SQLITE_DROP_TABLE
  - SQLITE_DROP_TEMP_INDEX
  - SQLITE_DROP_TEMP_TABLE
  - SQLITE_DROP_TEMP_TRIGGER
  - SQLITE_DROP_TEMP_VIEW
  - SQLITE_DROP_TRIGGER
  - SQLITE_DROP_VIEW
  - SQLITE_DROP_VTABLE
  - SQLITE_EMPTY
  - SQLITE_ERROR
  - SQLITE_EXPERIMENTAL
  - SQLITE_EXTERN
  - SQLITE_FAIL
  - SQLITE_FCNTL_CHUNK_SIZE
  - SQLITE_FCNTL_FILE_POINTER
  - SQLITE_FCNTL_LOCKSTATE
  - SQLITE_FCNTL_SIZE_HINT
  - SQLITE_FCNTL_SYNC_OMITTED
  - SQLITE_FLOAT
  - SQLITE_FORMAT
  - SQLITE_FULL
  - SQLITE_FUNCTION
  - SQLITE_GET_LOCKPROXYFILE
  - SQLITE_IGNORE
  - SQLITE_INDEX_CONSTRAINT_EQ
  - SQLITE_INDEX_CONSTRAINT_GE
  - SQLITE_INDEX_CONSTRAINT_GT
  - SQLITE_INDEX_CONSTRAINT_LE
  - SQLITE_INDEX_CONSTRAINT_LT
  - SQLITE_INDEX_CONSTRAINT_MATCH
  - SQLITE_INSERT
  - SQLITE_INTEGER
  - SQLITE_INTERNAL
  - SQLITE_INTERRUPT
  - SQLITE_IOCAP_ATOMIC
  - SQLITE_IOCAP_ATOMIC16K
  - SQLITE_IOCAP_ATOMIC1K
  - SQLITE_IOCAP_ATOMIC2K
  - SQLITE_IOCAP_ATOMIC32K
  - SQLITE_IOCAP_ATOMIC4K
  - SQLITE_IOCAP_ATOMIC512
  - SQLITE_IOCAP_ATOMIC64K
  - SQLITE_IOCAP_ATOMIC8K
  - SQLITE_IOCAP_SAFE_APPEND
  - SQLITE_IOCAP_SEQUENTIAL
  - SQLITE_IOCAP_UNDELETABLE_WHEN_OPEN
  - SQLITE_IOERR
  - SQLITE_IOERR_ACCESS
  - SQLITE_IOERR_BLOCKED
  - SQLITE_IOERR_CHECKRESERVEDLOCK
  - SQLITE_IOERR_CLOSE
  - SQLITE_IOERR_DELETE
  - SQLITE_IOERR_DIR_CLOSE
  - SQLITE_IOERR_DIR_FSYNC
  - SQLITE_IOERR_FSTAT
  - SQLITE_IOERR_FSYNC
  - SQLITE_IOERR_LOCK
  - SQLITE_IOERR_NOMEM
  - SQLITE_IOERR_RDLOCK
  - SQLITE_IOERR_READ
  - SQLITE_IOERR_SEEK
  - SQLITE_IOERR_SHMLOCK
  - SQLITE_IOERR_SHMMAP
  - SQLITE_IOERR_SHMOPEN
  - SQLITE_IOERR_SHMSIZE
  - SQLITE_IOERR_SHORT_READ
  - SQLITE_IOERR_TRUNCATE
  - SQLITE_IOERR_UNLOCK
  - SQLITE_IOERR_WRITE
  - SQLITE_LAST_ERRNO
  - SQLITE_LIMIT_ATTACHED
  - SQLITE_LIMIT_COLUMN
  - SQLITE_LIMIT_COMPOUND_SELECT
  - SQLITE_LIMIT_EXPR_DEPTH
  - SQLITE_LIMIT_FUNCTION_ARG
  - SQLITE_LIMIT_LENGTH
  - SQLITE_LIMIT_LIKE_PATTERN_LENGTH
  - SQLITE_LIMIT_SQL_LENGTH
  - SQLITE_LIMIT_TRIGGER_DEPTH
  - SQLITE_LIMIT_VARIABLE_NUMBER
  - SQLITE_LIMIT_VDBE_OP
  - SQLITE_LOCKED
  - SQLITE_LOCKED_SHAREDCACHE
  - SQLITE_LOCK_EXCLUSIVE
  - SQLITE_LOCK_NONE
  - SQLITE_LOCK_PENDING
  - SQLITE_LOCK_RESERVED
  - SQLITE_LOCK_SHARED
  - SQLITE_MISMATCH
  - SQLITE_MISUSE
  - SQLITE_MUTEX_FAST
  - SQLITE_MUTEX_RECURSIVE
  - SQLITE_MUTEX_STATIC_LRU
  - SQLITE_MUTEX_STATIC_LRU2
  - SQLITE_MUTEX_STATIC_MASTER
  - SQLITE_MUTEX_STATIC_MEM
  - SQLITE_MUTEX_STATIC_MEM2
  - SQLITE_MUTEX_STATIC_OPEN
  - SQLITE_MUTEX_STATIC_PMEM
  - SQLITE_MUTEX_STATIC_PRNG
  - SQLITE_NOLFS
  - SQLITE_NOMEM
  - SQLITE_NOTADB
  - SQLITE_NOTFOUND
  - SQLITE_NULL
  - SQLITE_OK
  - SQLITE_OPEN_AUTOPROXY
  - SQLITE_OPEN_CREATE
  - SQLITE_OPEN_DELETEONCLOSE
  - SQLITE_OPEN_EXCLUSIVE
  - SQLITE_OPEN_FULLMUTEX
  - SQLITE_OPEN_MAIN_DB
  - SQLITE_OPEN_MAIN_JOURNAL
  - SQLITE_OPEN_MASTER_JOURNAL
  - SQLITE_OPEN_NOMUTEX
  - SQLITE_OPEN_PRIVATECACHE
  - SQLITE_OPEN_READONLY
  - SQLITE_OPEN_READWRITE
  - SQLITE_OPEN_SHAREDCACHE
  - SQLITE_OPEN_SUBJOURNAL
  - SQLITE_OPEN_TEMP_DB
  - SQLITE_OPEN_TEMP_JOURNAL
  - SQLITE_OPEN_TRANSIENT_DB
  - SQLITE_OPEN_URI
  - SQLITE_OPEN_WAL
  - SQLITE_PERM
  - SQLITE_PRAGMA
  - SQLITE_PROTOCOL
  - SQLITE_RANGE
  - SQLITE_READ
  - SQLITE_READONLY
  - SQLITE_READONLY_CANTLOCK
  - SQLITE_READONLY_RECOVERY
  - SQLITE_REINDEX
  - SQLITE_REPLACE
  - SQLITE_ROLLBACK
  - SQLITE_ROW
  - SQLITE_SAVEPOINT
  - SQLITE_SCHEMA
  - SQLITE_SELECT
  - SQLITE_SET_LOCKPROXYFILE
  - SQLITE_SHM_EXCLUSIVE
  - SQLITE_SHM_LOCK
  - SQLITE_SHM_NLOCK
  - SQLITE_SHM_SHARED
  - SQLITE_SHM_UNLOCK
  - SQLITE_SOURCE_ID
  - SQLITE_STATIC
  - SQLITE_STATUS_MALLOC_COUNT
  - SQLITE_STATUS_MALLOC_SIZE
  - SQLITE_STATUS_MEMORY_USED
  - SQLITE_STATUS_PAGECACHE_OVERFLOW
  - SQLITE_STATUS_PAGECACHE_SIZE
  - SQLITE_STATUS_PAGECACHE_USED
  - SQLITE_STATUS_PARSER_STACK
  - SQLITE_STATUS_SCRATCH_OVERFLOW
  - SQLITE_STATUS_SCRATCH_SIZE
  - SQLITE_STATUS_SCRATCH_USED
  - SQLITE_STMTSTATUS_AUTOINDEX
  - SQLITE_STMTSTATUS_FULLSCAN_STEP
  - SQLITE_STMTSTATUS_SORT
  - SQLITE_SYNC_DATAONLY
  - SQLITE_SYNC_FULL
  - SQLITE_SYNC_NORMAL
  - SQLITE_TESTCTRL_ALWAYS
  - SQLITE_TESTCTRL_ASSERT
  - SQLITE_TESTCTRL_BENIGN_MALLOC_HOOKS
  - SQLITE_TESTCTRL_BITVEC_TEST
  - SQLITE_TESTCTRL_FAULT_INSTALL
  - SQLITE_TESTCTRL_FIRST
  - SQLITE_TESTCTRL_ISKEYWORD
  - SQLITE_TESTCTRL_LAST
  - SQLITE_TESTCTRL_LOCALTIME_FAULT
  - SQLITE_TESTCTRL_OPTIMIZATIONS
  - SQLITE_TESTCTRL_PENDING_BYTE
  - SQLITE_TESTCTRL_PGHDRSZ
  - SQLITE_TESTCTRL_PRNG_RESET
  - SQLITE_TESTCTRL_PRNG_RESTORE
  - SQLITE_TESTCTRL_PRNG_SAVE
  - SQLITE_TESTCTRL_RESERVE
  - SQLITE_TESTCTRL_SCRATCHMALLOC
  - SQLITE_TEXT
  - SQLITE_TOOBIG
  - SQLITE_TRANSACTION
  - SQLITE_TRANSIENT
  - SQLITE_UPDATE
  - SQLITE_UTF16
  - SQLITE_UTF16BE
  - SQLITE_UTF16LE
  - SQLITE_UTF16_ALIGNED
  - SQLITE_UTF8
  - SQLITE_VERSION
  - SQLITE_VERSION_NUMBER
  - SQLITE_VTAB_CONSTRAINT_SUPPORT
  - _GNU_SOURCE
  - _POSIX_C_SOURCE
  - _SQLITE3RTREE_H_
  - _SQLITE3_H_
  - double
*/

/* ====================================================================== */
/* COMPILATION NOTES */
/* ====================================================================== */
/*
This is a CALYX bundle - not meant for direct compilation.
To compile the original project:
  1. Extract files using the structure above
  2. Use the original build system (Makefile, CMake, etc.)
  3. Link with external dependencies:
     - openssl/sha.h
     - stdarg.h
     - stdbool.h
     - stddef.h
     - stdint.h
     - stdio.h
     - stdlib.h
     - string.h
     - sys/stat.h
     - time.h
*/

/* ====================================================================== */
/* HELPER FUNCTIONS (for analysis) */
/* ====================================================================== */
/*
To analyze this bundle programmatically:
  1. Parse CALYX_METADATA JSON string
  2. Scan for /* FILE: comments to locate files
  3. Use dependency graph for build order
  4. Extract functions using regex patterns
*/