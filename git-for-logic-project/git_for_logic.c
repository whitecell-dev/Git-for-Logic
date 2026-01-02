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
