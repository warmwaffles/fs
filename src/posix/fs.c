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

char*
fs_basename(const char* name)
{
    char const* p;
    char const* base = name;
    int all_slashes  = 1;

    for (p = name; *p; p++) {
        if (*p == '/') {
            base = p + 1;
        } else {
            all_slashes = 0;
        }
    }

    /* If NAME is all slashes, arrange to return `/'. */
    if (*base == '\0' && *name == '/' && all_slashes) {
        --base;
    }

    return (char*)base;
}

int
fs_chown(const char* path, int uid, int gid)
{
    return chown(path, (uid_t)uid, (gid_t)gid);
}

int
fs_delete(const char* file)
{
    assert(file);
    return unlink(file);
}

int
fs_fchown(FILE* file, int uid, int gid)
{
    int fd = fileno(file);
    return fchown(fd, (uid_t)uid, (gid_t)gid);
}

int
fs_lchown(const char* path, int uid, int gid)
{
    return lchown(path, (uid_t)uid, (gid_t)gid);
}

fs_stats*
fs_lstat(const char* path)
{
    fs_stats* stats = (fs_stats*)malloc(sizeof(fs_stats));
    int e           = lstat(path, stats);
    if (e == -1) {
        free(stats);
        return NULL;
    }

    return stats;
}

int
fs_mkdir(const char* path, int mode)
{
    return mkdir(path, (mode_t)mode);
}

int
fs_mkpath(const char* path)
{
    const int mode = 0755;
    char const* p;
    char npath[MAX_PATH + 1] = { 0 };
    int len                  = 0;

    for (p = path; *p && len < MAX_PATH; p++) {
        if (*p == '/' && len > 0) {
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
    return truncate(path, (off_t)len);
}
