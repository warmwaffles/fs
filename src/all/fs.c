#define _POSIX_C_SOURCE 200809L
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <assert.h>

#include <fs.h>

#define MAX_PATH 32767

int
fs_close(FILE* file)
{
    assert(file);
    return fclose(file);
}

void
fs_error(const char* prefix)
{
    assert(prefix);
    char fmt[256];
    sprintf(fmt, "fs: %s: error", prefix);
    perror(fmt);
}

int
fs_exists(const char* path)
{
    assert(path);
    struct stat b;
    return stat(path, &b) == 0;
}

int
fs_fgetc(FILE* stream)
{
    assert(stream);
    return fgetc(stream);
}

int
fs_fgetpos(FILE* stream, fpos_t* pos)
{
    assert(stream);
    return fgetpos(stream, pos);
}

size_t
fs_fread(void* ptr, size_t size, size_t nitems, FILE* stream)
{
    assert(ptr);
    assert(stream);

    return fread(ptr, size, nitems, stream);
}

int
fs_fseek(FILE* stream, long offset, int whence)
{
    assert(stream);
    return fseek(stream, offset, whence);
}

int
fs_fsetpos(FILE* stream, const fpos_t* pos)
{
    assert(stream);
    assert(pos);

    return fsetpos(stream, pos);
}

size_t
fs_fsize(FILE* file)
{
    assert(file);
    // store current position
    unsigned long pos = fs_ftell(file);
    fs_rewind(file);
    fs_fseek(file, 0, SEEK_END);
    size_t size = fs_ftell(file);
    // reset
    fs_fseek(file, pos, SEEK_SET);
    return size;
}

int
fs_fskip(FILE* stream, long offset)
{
    assert(stream);
    return fseek(stream, offset, SEEK_CUR);
}

fs_stats*
fs_fstat(FILE* file)
{
    assert(file);

    fs_stats* stats = (fs_stats*)malloc(sizeof(fs_stats));
    int fd          = fileno(file);
    int e           = fstat(fd, stats);
    if (e == -1) {
        free(stats);
        return NULL;
    }

    return stats;
}

long
fs_ftell(FILE* stream)
{
    assert(stream);
    return ftell(stream);
}

int
fs_ftruncate(FILE* file, size_t len)
{
    assert(file);
    int fd = fileno(file);
    return ftruncate(fd, (off_t)len);
}

size_t
fs_fwrite(const void* ptr, size_t size, size_t nitems, FILE* stream)
{
    assert(ptr);
    assert(stream);
    return fwrite(ptr, size, nitems, stream);
}

FILE*
fs_open(const char* path, const char* flags)
{
    assert(path);
    assert(flags);
    return fopen(path, flags);
}

int
fs_rename(const char* from, const char* to)
{
    assert(from);
    assert(to);
    return rename(from, to);
}

void
fs_rewind(FILE* stream)
{
    assert(stream);
    rewind(stream);
}

int
fs_rmdir(const char* path)
{
    assert(path);
    return rmdir(path);
}

size_t
fs_size(const char* path)
{
    assert(path);
    size_t size;
    FILE* file = fs_open(path, FS_OPEN_READ);
    if (file == NULL) {
        return -1;
    }

    fseek(file, 0, SEEK_END);
    size = ftell(file);
    fs_close(file);

    return size;
}

fs_stats*
fs_stat(const char* path)
{
    assert(path);
    fs_stats* stats = (fs_stats*)malloc(sizeof(fs_stats));
    int e           = stat(path, stats);
    if (e == -1) {
        free(stats);
        return NULL;
    }

    return stats;
}
