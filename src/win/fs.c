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

#define HAS_DEVICE(P) ((((P)[0] >= 'A' && (P)[0] <= 'Z') || ((P)[0] >= 'a' && (P)[0] <= 'z')) && (P)[1] == ':')
#define FILESYSTEM_PREFIX_LEN(P) (HAS_DEVICE(P) ? 2 : 0)
#define ISSLASH(C) ((C) == '/' || (C) == '\\')

#define MAX_PATH 32767

char*
fs_basename(const char* name)
{
    char const* p;
    char const* base = name += FILESYSTEM_PREFIX_LEN(name);
    int all_slashes  = 1;

    for (p = name; *p; p++) {
        if (ISSLASH(*p)) {
            base = p + 1;
        } else {
            all_slashes = 0;
        }
    }

    /* If NAME is all slashes, arrange to return `/'. */
    if (*base == '\0' && ISSLASH(*name) && all_slashes) {
        --base;
    }

    return (char*)base;
}

int
fs_chown(const char* path, int uid, int gid)
{
    errno = ENOSYS;
    return -1;
}

int
fs_delete(const char* file)
{
    assert(file);
    return DeleteFileA(file) ? 0 : -1;
}

int
fs_fchown(FILE* file, int uid, int gid)
{
    errno = ENOSYS;
    return -1;
}

int
fs_lchown(const char* path, int uid, int gid)
{
    errno = ENOSYS;
    return -1;
}

fs_stats*
fs_lstat(const char* path)
{
    fs_stats* stats = (fs_stats*)malloc(sizeof(fs_stats));
    int e           = stat(path, stats);
    if (e == -1) {
        free(stats);
        return NULL;
    }
    return stats;
}

int
fs_mkdir(const char* path, int mode)
{
    return mkdir(path);
}

int
fs_mkpath(const char* path)
{
    const int mode = 0755;
    char const* p;
    char npath[MAX_PATH + 1] = { 0 };
    int len                  = 0;

    for (p = path; *p && len < MAX_PATH; p++) {
        if (ISSLASH(*p) && len > 0) {
            if (fs_mkdir(npath, mode) == -1) {
                if (errno != EEXIST) {
                    return -1;
                }
            }
        }
        npath[len++] = *p;
    }

    return 0;
}

int
fs_truncate(const char* path, size_t len)
{
    int ret = -1;
    int fd  = open(path, O_RDWR | O_CREAT, S_IREAD | S_IWRITE);
    if (fd != -1) {
        ret = ftruncate(fd, (off_t)len);
        close(fd);
    }
    return ret;
}
