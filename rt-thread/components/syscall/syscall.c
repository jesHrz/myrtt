#include <syscall.h>
#include <rtthread.h>
#include <rtdef.h>

#ifdef RT_USING_DFS
#include <dfs_posix.h>
#endif

#ifdef RT_USING_MODULE
#include <dlmodule.h>
#endif

int sys_exit(struct stack_frame *sp)
{
    rt_thread_exit();
    return 0;
}

int sys_read(struct stack_frame *sp)
{
    int     fd = (int)sp->exception_stack_frame.r0;
    void  *buf = (void *)sp->exception_stack_frame.r1;
    size_t len = (size_t)sp->exception_stack_frame.r2;
#ifdef RT_USING_DFS
    return read(fd, buf, len);
#else
    return -ENOSYS;
#endif
}

int sys_write(struct stack_frame *sp)
{
    int          fd = (int)sp->exception_stack_frame.r0;
    const void *buf = (const void *)sp->exception_stack_frame.r1;
    size_t   nbytes = (size_t)sp->exception_stack_frame.r2;
#ifndef RT_USING_DFS
#ifdef RT_USING_DEVICE
    if (fileno(stdout) == fd)
    {
        rt_device_t console;

        console = rt_console_get_device();
        if (console) return rt_device_write(console, -1, buf, nbytes);
    }

    return 0;
#else
    /* return "not supported" */
    return -ENOSYS;
#endif /*RT_USING_DEVICE*/
#else
    return write(fd, buf, nbytes);
#endif
}

int sys_lseek(struct stack_frame *sp)
{
    int       fd = (int)sp->exception_stack_frame.r0;
    off_t offset = (off_t)sp->exception_stack_frame.r1;
    int   whence = (int)sp->exception_stack_frame.r2;
#ifdef RT_USING_DFS
    return (int)lseek(fd, offset, whence);
#else
    return -ENOSYS;
#endif
}

int sys_open(struct stack_frame *sp)
{
    const char *name = (const char *)sp->exception_stack_frame.r0;
    int        flags = (int)sp->exception_stack_frame.r1;
    int         mode = (int)sp->exception_stack_frame.r2;
#ifdef RT_USING_DFS
    return open(name, flags, mode);
#else
    return -ENOSYS;
#endif
}

int sys_close(struct stack_frame *sp)
{
    int fd = (int)sp->exception_stack_frame.r0;
#ifdef RT_USING_DFS
    return close(fd);
#else
    return -ENOSYS;
#endif
}

int sys_rename(struct stack_frame *sp)
{
    const char *old_file = (const char *)sp->exception_stack_frame.r0;
    const char *new_file = (const char *)sp->exception_stack_frame.r1;
#ifdef RT_USING_DFS
    return rename(old_file, new_file);
#else
    return -ENOSYS;
#endif
}

int sys_stat(struct stack_frame *sp)
{
    const char *file = (const char *)sp->exception_stack_frame.r0;
    struct stat *buf = (struct stat *)sp->exception_stack_frame.r1;
#ifdef RT_USING_DFS
    return stat(file, buf);
#else
    return -ENOSYS;
#endif
}

int sys_fstat(struct stack_frame *sp)
{
    int          file = (int)sp->exception_stack_frame.r0;
    struct stat  *buf = (struct stat *)sp->exception_stack_frame.r1;
#ifdef RT_USING_DFS
    return fstat(file, buf);
#else
    return -ENOSYS;
#endif
}

int sys_fsync(struct stack_frame *sp)
{
    int fildes = (int)sp->exception_stack_frame.r0;
#ifdef RT_USING_DFS
    return fsync(fildes);
#else
    return -ENOSYS;
#endif
}

int sys_fcntl(struct stack_frame *sp)
{
    int  fildes = (int)sp->exception_stack_frame.r0;
    int     cmd = (int)sp->exception_stack_frame.r1;
    void  *args = (void *)sp->exception_stack_frame.r2;
#ifdef RT_USING_DFS
    return fcntl(fildes, cmd, args);
#else
    return -ENOSYS;
#endif
}

int sys_ioctl(struct stack_frame *sp)
{
    int            fd = (int)sp->exception_stack_frame.r0;
    unsigned long cmd = (unsigned long)sp->exception_stack_frame.r1;
    void        *data = (void *)sp->exception_stack_frame.r2;
#ifdef RT_USING_DFS
    return ioctl(fd, cmd, data);
#else
    return -ENOSYS;
#endif
}

int sys_nanosleep(struct stack_frame *sp)
{
    const struct timespec *rqtp = (const struct timespec *)sp->exception_stack_frame.r0;
    struct timespec       *rmtp = (struct timespec *)sp->exception_stack_frame.r1;

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

int sys_gettimeofday(struct stack_frame *sp)
{
    struct timeval  *tp = (struct timeval *)sp->exception_stack_frame.r0;
    struct timeval *tzp = (struct timeval *)sp->exception_stack_frame.r0;

    if (tp)
    {
        tp->tv_sec = rt_tick_get() / RT_TICK_PER_SECOND;
        tp->tv_usec = (rt_tick_get() % RT_TICK_PER_SECOND) * (1000000 / RT_TICK_PER_SECOND);
    }

    return 0;
}

int sys_settimeofday(struct stack_frame *sp)
{
    return 0;
}

int sys_errno(struct stack_frame *sp)
{
    return (int)_rt_errno();
}

int sys_mkdir(struct stack_frame *sp)
{
    const char *path = (const char *)sp->exception_stack_frame.r0;
    int         mode = (int)sp->exception_stack_frame.r1;
#ifdef RT_USING_DFS
    return mkdir(path, mode);
#else
    return -ENOSYS;
#endif
}

int sys_unlink(struct stack_frame *sp)
{
    const char *pathname = (const char *)sp->exception_stack_frame.r0;
#ifdef RT_USING_DFS
    return unlink(pathname);
#else
    return -ENOSYS;
#endif
}

int sys_malloc(struct stack_frame *sp)
{
    size_t size = (size_t)sp->exception_stack_frame.r0;
    return (int)rt_malloc(size);
}

int sys_realloc(struct stack_frame *sp)
{
    void     *old = (void *)sp->exception_stack_frame.r0;
    size_t newlen = (size_t)sp->exception_stack_frame.r1;
    return (int)rt_realloc(old, newlen);
}

int sys_calloc(struct stack_frame *sp)
{
    size_t size = (size_t)sp->exception_stack_frame.r0;
    size_t  len = (size_t)sp->exception_stack_frame.r1;
    return (int)rt_calloc(size, len);
}

int sys_free(struct stack_frame *sp)
{
    void *addr = (void *)sp->exception_stack_frame.r0;
    rt_free(addr);
    return 0;
}

int sys_dlmodule_init(struct stack_frame *sp)
{
    int   *argc = (int *)sp->exception_stack_frame.r0;
    char **argv = (char **)sp->exception_stack_frame.r1;

#ifdef RT_USING_MODULE
    return dlmodule_init(argc, argv);
#else
    return -ENOSYS;
#endif
}

int sys_dlmodule_cleanup(struct stack_frame *sp)
{
    int ret_code = (int)sp->exception_stack_frame.r0;

#ifdef RT_USING_MODULE
    dlmodule_cleanup(ret_code);
    return 0;
#else
    return -ENOSYS;
#endif
}

void *syscall_table[NR_SYSCALL] = {
    [SYS_exit]              = (void *)sys_exit,
    [SYS_read]              = (void *)sys_read,
    [SYS_write]             = (void *)sys_write,
    [SYS_lseek]             = (void *)sys_lseek,
    [SYS_open]              = (void *)sys_open,
    [SYS_close]             = (void *)sys_close,
    [SYS_rename]            = (void *)sys_rename,
    [SYS_stat]              = (void *)sys_stat,
    [SYS_fstat]             = (void *)sys_fstat,
    [SYS_fsync]             = (void *)sys_fsync,
    [SYS_fcntl]             = (void *)sys_fcntl,
    [SYS_ioctl]             = (void *)sys_ioctl,
    [SYS_nanosleep]         = (void *)sys_nanosleep,
    [SYS_gettimeofday]      = (void *)sys_gettimeofday,
    [SYS_settimeofday]      = (void *)sys_settimeofday,
    [SYS_errno]             = (void *)sys_errno,
    [SYS_mkdir]             = (void *)sys_mkdir,
    [SYS_unlink]            = (void *)sys_unlink,
    [SYS_malloc]            = (void *)sys_malloc,
    [SYS_realloc]           = (void *)sys_realloc,
    [SYS_calloc]            = (void *)sys_calloc,
    [SYS_free]              = (void *)sys_free,
    [SYS_dlmodule_init]     = (void *)sys_dlmodule_init,
    [SYS_dlmodule_cleanup]     = (void *)sys_dlmodule_cleanup,
};


struct exception_stack_frame *
do_syscall(struct stack_frame *context)
{
    int rc = -ENOSYS;
    int sys_nr = context->r8;

    if (sys_nr >= 0 && sys_nr < NR_SYSCALL)
        rc = ((int(*)(struct stack_frame *sp))syscall_table[sys_nr])(context);

    context->exception_stack_frame.r0 = rc;
    return &context->exception_stack_frame;
}