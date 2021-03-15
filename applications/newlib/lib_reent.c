#include <reent.h>
#include <errno.h>
#include <stdio.h>
#include <sys/time.h>

#include "lib_syscalls.h"
#include "include/syscall.h"

#define ENOSYS                  88

#ifndef _REENT_ONLY
int *
__errno ()
{
  return sys_errno();
}
#endif

int
_getpid_r(struct _reent *ptr)
{
    return 0;
}

int
_close_r(struct _reent *ptr, int fd)
{
    int ret = sys_close(fd);
    if (ret != -ENOSYS)
        return ret;
    ptr->_errno = ENOTSUP;
    return -1;
}

int
_execve_r(struct _reent *ptr, const char * name, char *const *argv, char *const *env)
{
    /* return "not supported" */
    ptr->_errno = ENOTSUP;
    return -1;
}

int
_fcntl_r(struct _reent *ptr, int fd, int cmd, int arg)
{
    int ret = sys_fcntl(fd, cmd, (void *)arg);
    if (ret != -ENOSYS)
        return ret;
    /* return "not supported" */
    ptr->_errno = ENOTSUP;
    return -1;
}

int
_fork_r(struct _reent *ptr)
{
    /* return "not supported" */
    ptr->_errno = ENOTSUP;
    return -1;
}

int
_fstat_r(struct _reent *ptr, int fd, struct stat *pstat)
{
    // int ret = sys_fstat(fd, pstat);
    // if (ret != -ENOSYS)
    //     return ret;
    /* return "not supported" */
    ptr->_errno = ENOTSUP;
    return -1;
}

int
_isatty_r(struct _reent *ptr, int fd)
{
    if (fd >=0 && fd < 3)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int
_kill_r(struct _reent *ptr, int pid, int sig)
{
    /* return "not supported" */
    ptr->_errno = ENOTSUP;
    return -1;
}

int
_link_r(struct _reent *ptr, const char *old, const char *new)
{
    /* return "not supported" */
    ptr->_errno = ENOTSUP;
    return -1;
}

_off_t
_lseek_r(struct _reent *ptr, int fd, _off_t pos, int whence)
{
    _off_t ret = (_off_t)sys_lseek(fd, pos, whence);
    if (ret != -ENOSYS)
        return ret;
    /* return "not supported" */
    ptr->_errno = ENOTSUP;
    return -1;
}

int
_mkdir_r(struct _reent *ptr, const char *name, int mode)
{
    int ret = sys_mkdir(name, mode);
    if (ret != -ENOSYS)
        return ret;
    /* return "not supported" */
    ptr->_errno = ENOTSUP;
    return -1;
}

int
_open_r(struct _reent *ptr, const char *file, int flags, int mode)
{
    int ret = sys_open(file, flags, mode);
    if (ret != -ENOSYS)
        return ret;
    /* return "not supported" */
    ptr->_errno = ENOTSUP;
    return -1;
}

_ssize_t
_read_r(struct _reent *ptr, int fd, void *buf, size_t nbytes)
{
    _ssize_t ret = (_ssize_t)sys_read(fd, buf, nbytes);
    if (ret != -ENOSYS)
        return ret;
    /* return "not supported" */
    ptr->_errno = ENOTSUP;
    return -1;
}

int
_rename_r(struct _reent *ptr, const char *old, const char *new)
{
    int ret = sys_rename(old, new);
    if (ret != -ENOSYS)
        return ret;
    /* return "not supported" */
    ptr->_errno = ENOTSUP;
    return -1;
}

int
_stat_r(struct _reent *ptr, const char *file, struct stat *pstat)
{
    int ret = sys_stat(file, pstat);
    if (ret != -ENOSYS)
        return ret;
    /* return "not supported" */
    ptr->_errno = ENOTSUP;
    return -1;
}

int
_unlink_r(struct _reent *ptr, const char *file)
{
    int ret = sys_unlink(file);
    if (ret != -ENOSYS)
        return ret;
    /* return "not supported" */
    ptr->_errno = ENOTSUP;
    return -1;
}

int
_wait_r(struct _reent *ptr, int *status)
{
    /* return "not supported" */
    ptr->_errno = ENOTSUP;
    return -1;
}

_ssize_t
_write_r(struct _reent *ptr, int fd, const void *buf, size_t nbytes)
{
    int ret = sys_write(fd, buf, nbytes);
    if (ret != -ENOSYS)
        return ret;
    /* return "not supported" */
    ptr->_errno = ENOTSUP;
    return -1;
}

void *
_malloc_r (struct _reent *ptr, size_t size)
{
    void* result;

    result = (void*)sys_malloc(size);
    if (result == NULL)
    {
        ptr->_errno = ENOMEM;
    }

    return result;
}

void *
_realloc_r (struct _reent *ptr, void *old, size_t newlen)
{
    void* result;

    result = (void*)sys_realloc(old, newlen);
    if (result == NULL)
    {
        ptr->_errno = ENOMEM;
    }

    return result;
}

void *_calloc_r (struct _reent *ptr, size_t size, size_t len)
{
    void* result;

    result = (void*)sys_calloc(size, len);
    if (result == NULL)
    {
        ptr->_errno = ENOMEM;
    }

    return result;
}

void
_free_r (struct _reent *ptr, void *addr)
{
    sys_free(addr);
}

/* for exit() and abort() */
__attribute__ ((noreturn)) void
_exit (int status)
{
    sys_exit();
    /* !!! should not reach there !!! */
    while(1);
}

mode_t umask(mode_t mask)
{
    return 022;
}

int flock(int fd, int operation)
{
    return 0;
}