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
