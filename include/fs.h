#pragma once

#include <stdio.h>
#include <sys/stat.h>

#include <stddef.h>
#include <stdbool.h>

#ifdef _WIN32
#define FS_OPEN_READ "rb"
#define FS_OPEN_WRITE "wb"
#define FS_OPEN_READWRITE "rwb"
#else
#define FS_OPEN_READ "r"
#define FS_OPEN_WRITE "w"
#define FS_OPEN_READWRITE "rw"
#endif

typedef struct stat fs_stats;

long fs_ftell(FILE* stream);
void fs_rewind(FILE* stream);
int fs_fgetpos(FILE* stream, fpos_t* pos);
int fs_fsetpos(FILE* stream, const fpos_t* pos);
int fs_fgetc(FILE* stream);
int fs_fseek(FILE* stream, long offset, int whence);
int fs_fskip(FILE* stream, long offset);

int fs_delete(const char* file);

char* fs_basename(const char* filename);
int fs_mkpath(const char* path);

/// @brief Prints the last error to stderr
void fs_error(const char* prefix);

/// @brief Opens a file with given flags and returns a file descriptor
FILE* fs_open(const char* path, const char* flags);

/// @brief Closes a given file descriptor
int fs_close(FILE* file);

/// @brief Moves a path to a new destination
int fs_rename(const char* from, const char* to);

/// @brief Stats a given path and returns a `struct stat`
fs_stats* fs_stat(const char* path);

/// @brief Stats a given file descriptor
fs_stats* fs_fstat(FILE* file);

/// @brief Stats a given link path
fs_stats* fs_lstat(const char* path);

/// @brief Truncates a file to a specified length from a given file descriptor
int fs_ftruncate(FILE* file, size_t len);

/// @brief Truncates a file to a specified len from a given file path
int fs_truncate(const char* path, size_t len);

/// @brief Changes ownership of a given file path to a given owner and group
int fs_chown(const char* path, int uid, int gid);

/// @brief Change ownership of a given file descriptor to a given owner and
///        group.
int fs_fchown(FILE* file, int uid, int gid);

/// @brief Returns the size of a file from a given file path
size_t fs_size(const char* path);

/// @brief Returns the size of a file from a given file descriptor
size_t fs_fsize(FILE* file);

/// @brief Change ownership of a given link path to a given owner and group
///
/// @param [in] path
/// @param [in] uid
/// @param [in] gid
///
/// @return 1 if successful, otherwise 0
int fs_lchown(const char* path, int uid, int gid);

/// @brief A wrapper around stdio fread
///
/// @param [in] ptr
/// @param [in] size
/// @param [in] nitems
/// @param [in] stream
///
/// @return
size_t fs_fread(void* ptr, size_t size, size_t nitems, FILE* stream);

/// @brief Writes a buffer to a given file stream
size_t fs_fwrite(const void* ptr, size_t size, size_t nitems, FILE* stream);

/// @brief Makes a directory and returns 0 on success or -1 on failure
int fs_mkdir(const char* path, int mode);

/// @brief Removes a directory and returns 0 on success and -1 on failure
int fs_rmdir(const char* path);

/// @brief Check if the given `path` exists
int fs_exists(const char* path);
