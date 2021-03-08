#include <syscall.h>
#include <rtthread.h>
#include <rtdef.h>
#ifndef RT_USING_DFS
    #error "syscall depends on RT_USING_DFS"
#endif
#include <dfs_posix.h>

typedef void (*rt_fn_ptr)(void);

#define SVCALL_ENTRY(__fn) (rt_fn_ptr)(SVCALL_PREFIX(__fn))
#define SVCALL_PREFIX(__fn) rt_svc_##__fn

int SVCALL_PREFIX(exit)()
{
    rt_thread_exit();
    return 0;
}

int SVCALL_PREFIX(read)(int fd, void *buf, size_t len)
{
    return read(fd, buf, len);
}

int SVCALL_PREFIX(write)(int fd, const void *buf, size_t len)
{
    return write(fd, buf, len);
}

/* syscall: "lseek" ret: "off_t" args: "int" "off_t" "int" */
off_t SVCALL_PREFIX(lseek)(int fd, off_t offset, int whence)
{
    return lseek(fd, offset, whence);
}

/* syscall: "open" ret: "int" args: "const char *" "int" "..." */
int SVCALL_PREFIX(open)(const char *name, int mode, ...)
{
    return open(name, mode, 0);
}

/* syscall: "close" ret: "int" args: "int" */
int SVCALL_PREFIX(close)(int fd)
{
    return close(fd);
}

int SVCALL_PREFIX(rename)(const char *old_file, const char *new_file)
{
    return rename(old_file, new_file);
}

int SVCALL_PREFIX(stat)(const char *file, struct stat *buf)
{
    return stat(file, buf);
}

int SVCALL_PREFIX(fstat)(int file, struct stat *buf)
{
    return fstat(file, buf);
}

int SVCALL_PREFIX(fsync)(int fildes)
{
    return fsync(fildes);
}

int SVCALL_PREFIX(fcntl)(int fildes, int cmd, void *args)
{
    return _fcntl(fildes, cmd, args);
}

/* syscall: "ioctl" ret: "int" args: "int" "u_long" "..." */
int SVCALL_PREFIX(ioctl)(int fd, unsigned long cmd, void* data)
{
    return ioctl(fd, cmd, data);
}

/* syscall: "nanosleep" ret: "int" args: "const struct timespec *" "struct timespec *" */
int SVCALL_PREFIX(nanosleep)(const struct timespec *rqtp, struct timespec *rmtp)
{
    rt_tick_t tick;

    tick = rqtp->tv_sec * RT_TICK_PER_SECOND + (rqtp->tv_nsec * RT_TICK_PER_SECOND)/ 1000000000;
    rt_thread_delay(tick);

    if (rmtp)
    {
        tick = rt_tick_get() - tick;
        /* get the passed time */
        rmtp->tv_sec = tick/RT_TICK_PER_SECOND;
        rmtp->tv_nsec = (tick%RT_TICK_PER_SECOND) * (1000000000/RT_TICK_PER_SECOND);
    }

    return 0;
}

/* syscall: "gettimeofday" ret: "int" args: "struct timeval *" "struct timezone *" */
int SVCALL_PREFIX(gettimeofday)(struct timeval *tp, struct timezone *tzp)
{
    if (tp)
    {
        tp->tv_sec = rt_tick_get() / RT_TICK_PER_SECOND;
        tp->tv_usec = (rt_tick_get() % RT_TICK_PER_SECOND) * (1000000 / RT_TICK_PER_SECOND);
    }

    return 0;
}

/* syscall: "settimeofday" ret: "int" args: "const struct timeval *" "const struct timezone *" */
int SVCALL_PREFIX(settimeofday)(const struct timeval *tv, const struct timezone *tzp)
{
    return 0;
}

/* syscall: "msgget" ret: "int" args: "key_t" "int" */
int SVCALL_PREFIX(msgget)(key_t key, int msgflg)
{
    return -ENOSYS;
}

/* syscall: "msgsnd" ret: "int" args: "int" "const void *" "size_t" "int" */
int SVCALL_PREFIX(msgsend)(int msqid, const void *msgp, size_t msgsz, int msgflg)
{
    return -ENOSYS;
}

/* syscall: "msgrcv" ret: "int" args: "int" "void *" "size_t" "long" "int" */
int SVCALL_PREFIX(msgrcv)(int msqid, void *msgp, size_t msgsz, long msgtyp, int msgflg)
{
    return -ENOSYS;
}

/* syscall: "sys_log" ret: "int" args: "const char*" "size" */
int SVCALL_PREFIX(log)(const char* log, int size)
{
    rt_device_t console = rt_console_get_device();

    if (console) rt_device_write(console, -1, log, size);

    return 0;
}


rt_fn_ptr svcall_table[] = {
    SVCALL_ENTRY(exit),
    SVCALL_ENTRY(read),
    SVCALL_ENTRY(write),
    SVCALL_ENTRY(open),
    SVCALL_ENTRY(close),
    SVCALL_ENTRY(lseek),
    SVCALL_ENTRY(open),
    SVCALL_ENTRY(close),
    SVCALL_ENTRY(rename),
    SVCALL_ENTRY(stat),
    SVCALL_ENTRY(fstat),
    SVCALL_ENTRY(fsync),
    SVCALL_ENTRY(fcntl),
    SVCALL_ENTRY(ioctl),
    SVCALL_ENTRY(nanosleep),
    SVCALL_ENTRY(gettimeofday),
    SVCALL_ENTRY(settimeofday),
    SVCALL_ENTRY(msgget),
    SVCALL_ENTRY(msgsend),
    SVCALL_ENTRY(msgrcv),
    SVCALL_ENTRY(log)
};