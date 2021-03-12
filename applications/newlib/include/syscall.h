#ifndef __INCLUDE_SYSCALL_H_
#define __INCLUDE_SYSCALL_H_

#include <stddef.h>
#include <sys/types.h>
#include <sys/stat.h>

int sys_exit();
int sys_read(int fd, void *buf, size_t len);
int sys_write(int fd, const void *buf, size_t len);
int sys_lseek(int fd, off_t offset, int whence);
int sys_open(const char *name, int flags, int mode);
int sys_close(int fd);
int sys_rename(const char *old_file, const char *new_file);
int sys_stat(const char *file, struct stat *buf);
int sys_fstat(int file, struct stat *buf);
int sys_fsync(int fildes);
int sys_fcntl(int fildes, int cmd, void *arg);
int sys_ioctl(int fd, unsigned long cmd, void *data);
int sys_nanosleep(const struct timespec *rqtp, struct timespec *rmtp);
int sys_gettimeofday(struct timeval *tp, struct timezone *tzp);
int sys_settimeofday(struct timeval *tp, struct timezone *tzp);
int sys_errno();
int sys_mkdir(const char *path, int mode);
int sys_unlink(const char *pathname);
int sys_malloc(size_t size);
int sys_realloc(void *old, size_t newlen);
int sys_calloc(size_t size, size_t len);
int sys_free(void *addr);

#endif // __INCLUDE_SYSCALL_H_