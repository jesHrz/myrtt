#include "lib_syscalls.h"
#include <stddef.h>
#include <sys/types.h>
#include <sys/stat.h>

extern long syscall_0(int);
extern long syscall_1(int, long);
extern long syscall_2(int, long, long);
extern long syscall_3(int, long, long, long);
extern long syscall_4(int, long, long, long, long);


int sys_exit()
{
    return syscall_0(SYS_exit);
}

int sys_read(int fd, void *buf, size_t len)
{
    return syscall_3(SYS_read, (long)fd, (long)buf, (long)len);
}

int sys_write(int fd, const void *buf, size_t len)
{
    return syscall_3(SYS_write, (long)fd, (long)buf, (long)len);
}

off_t sys_lseek(int fd, off_t offset, int whence)
{
    return (off_t)syscall_3(SYS_lseek, (long)fd, (long)offset, (long)whence);
}

int sys_open(const char *name, int flags, int mode)
{
    return syscall_3(SYS_open, (long)name, (long)flags, (long)mode);
}

int sys_close(int fd)
{
    return syscall_1(SYS_close, (long)fd);
}

int sys_rename(const char *old_file, const char *new_file)
{
    return syscall_2(SYS_rename, (long)old_file, (long)new_file);
}

int sys_stat(const char *file, struct stat *buf)
{
    return syscall_2(SYS_stat, (long)file, (long)buf);
}

int sys_fstat(int file, struct stat *buf)
{
    return syscall_2(SYS_fstat, (long)file, (long)buf);
}

int sys_fsync(int fildes)
{
    return syscall_1(SYS_fsync, (long)fildes);
}

int sys_fcntl(int fildes, int cmd, void *arg)
{
    return syscall_3(SYS_fcntl, (long)fildes, (long)cmd, (long)arg);
}

int sys_ioctl(int fd, unsigned long cmd, void *data)
{
    return syscall_3(SYS_ioctl, (long)fd, (long)cmd, (long)data);
}

int sys_nanosleep(const struct timespec *rqtp, struct timespec *rmtp)
{
    return syscall_2(SYS_nanosleep, (long)rqtp, (long)rmtp);
}

int sys_gettimeofday(struct timeval *tp, struct timezone *tzp)
{
    return syscall_2(SYS_gettimeofday, (long)tp, (long)tzp);
}

int sys_settimeofday(struct timeval *tp, struct timezone *tzp)
{
    return syscall_2(SYS_settimeofday, (long)tp, (long)tzp);
}

int *sys_errno()
{
    return (int *)syscall_0(SYS_errno);
}

int sys_mkdir(const char *path, int mode)
{
    return syscall_2(SYS_mkdir, (long)path,(long) mode);
}

int sys_unlink(const char *pathname)
{
    return syscall_1(SYS_unlink, (long)pathname);
}

int sys_malloc(size_t size)
{
    return syscall_1(SYS_malloc, (long)size);
}

int sys_realloc(void *old, size_t newlen)
{
    return syscall_2(SYS_realloc, (long)old, (long)newlen);
}

int sys_calloc(size_t size, size_t len)
{
    return syscall_2(SYS_calloc, (long)size, (long)len);
}

int sys_free(void *addr)
{
    return syscall_1(SYS_free, (long)addr);
}
