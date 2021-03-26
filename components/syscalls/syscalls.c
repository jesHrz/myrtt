#include <syscalls.h>
#include <rtthread.h>
#include <rtdef.h>

#ifdef RT_USING_DFS
#include <dfs_posix.h>
#endif

#ifdef RT_USING_MODULE
#include <dlmodule.h>
#endif

int
sys_exit (int rc)
{
    rt_thread_exit();
    return 0;
}

int
sys_read (int    fd,
          void  *buf,
          size_t len)
{
#ifdef RT_USING_DFS
    return read(fd, buf, len);
#else
    return -ENOTSUP;
#endif
}

int
sys_write (int          fd,
           const void  *buf,
           size_t       nbytes)
{
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
    return -ENOTSUP;
#endif /*RT_USING_DEVICE*/
#else
    return write(fd, buf, nbytes);
#endif
}

int
sys_lseek (int   fd,
           off_t offset,
           int   whence)
{
#ifdef RT_USING_DFS
    return (int)lseek(fd, offset, whence);
#else
    return -ENOTSUP;
#endif
}

int
sys_open (const char *name,
          int         flags,
          int         mode)
{
#ifdef RT_USING_DFS
    return open(name, flags, mode);
#else
    return -ENOTSUP;
#endif
}

int 
sys_close (int fd)
{
#ifdef RT_USING_DFS
    return close(fd);
#else
    return -ENOTSUP;
#endif
}

int 
sys_rename (const char *old,
            const char *new)
{
#ifdef RT_USING_DFS
    return rename(old, new);
#else
    return -ENOTSUP;
#endif
}

int
sys_stat (const char  *name,
          struct stat *buf)
{
#ifdef RT_USING_DFS
    return stat(name, buf);
#else
    return -ENOSYS;
#endif
}

int 
sys_fstat (int          file,
           struct stat *buf)
{
#ifdef RT_USING_DFS
    return fstat(file, buf);
#else
    return -ENOTSUP;
#endif
}

int
sys_fsync (int file)
{
#ifdef RT_USING_DFS
    return fsync(file);
#else
    return -ENOTSUP;
#endif
}

int
sys_fcntl (int   file,
           int   cmd,
           void *args)
{
#ifdef RT_USING_DFS
    return fcntl(file, cmd, args);
#else
    return -ENOTSUP;
#endif
}

int
sys_ioctl (int           file,
           unsigned long cmd,
           void         *data)
{
#ifdef RT_USING_DFS
    return ioctl(file, cmd, data);
#else
    return -ENOTSUP;
#endif
}

int
sys_nanosleep (const struct timespec *rqtp,
               struct timespec       *rmtp)
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

int
sys_gettimeofday (struct timeval *tp,
                  struct timeval *tzp)
{
    if (tp)
    {
        tp->tv_sec = rt_tick_get() / RT_TICK_PER_SECOND;
        tp->tv_usec = (rt_tick_get() % RT_TICK_PER_SECOND) * (1000000 / RT_TICK_PER_SECOND);
    }

    return 0;
}

int
sys_settimeofday (struct timeval *tp,
                  struct timeval *tzp)
{
    return -ENOSYS;
}

int
sys_errno()
{
    return (int)_rt_errno();
}

int
sys_mkdir (const char *path,
           int         mode)
{
#ifdef RT_USING_DFS
    return mkdir(path, mode);
#else
    return -ENOTSUP;
#endif
}

int
sys_unlink (const char *path)
{
#ifdef RT_USING_DFS
    return unlink(path);
#else
    return -ENOTSUP;
#endif
}

int
sys_malloc (size_t size)
{
    return (int)rt_malloc(size);
}

int
sys_realloc (void  *old,
             size_t newlen)
{
    return (int)rt_realloc(old, newlen);
}

int
sys_calloc (size_t size,
            size_t len)
{
    return (int)rt_calloc(size, len);
}

int
sys_free (void *addr)
{
    rt_free(addr);
    return 0;
}

// int
// sys_dlmodule_init (int   *argc,
//                    char **argv)
// {
// #ifdef RT_USING_MODULE
//     return dlmodule_init(argc, argv);
// #else
//     return -ENOTSUP;
// #endif
// }

// int
// sys_dlmodule_cleanup (int rc)
// {
// #ifdef RT_USING_MODULE
//     dlmodule_cleanup(rc);
//     return 0;
// #else
//     return -ENOTSUP;
// #endif
// }

// extern int sys_signal(struct stack_frame *);
// extern int sys_kill(struct stack_frame *);
// extern int sys_sigreturn(struct stack_frame *);
// extern int sys_sigprocmask(struct stack_frame *);

int
sys_getpid ()
{
    return (int)rt_thread_self();
}

int
sys_getpidbyname(const char *name)
{
    struct rt_object_information *information;
    struct rt_thread *thread;
    rt_list_t *p;

    information = rt_object_get_information(RT_Object_Class_Thread);
    RT_ASSERT(information != RT_NULL);

    for (p = information->object_list.next; p != &information->object_list; p = p->next)
    {
        thread = rt_container_of(p, struct rt_thread, list);
        if (strcmp(thread->name, name) == 0)
            return (int)thread;
    }
    return -1;
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
    // [SYS_dlmodule_init]     = (void *)sys_dlmodule_init,
    // [SYS_dlmodule_cleanup]  = (void *)sys_dlmodule_cleanup,
    // [SYS_signal]            = (void *)sys_signal,
    // [SYS_kill]              = (void *)sys_kill,
    // [SYS_sigreturn]         = (void *)sys_sigreturn,
    [SYS_getpid]            = (void *)sys_getpid,
    [SYS_getpidbyname]      = (void *)sys_getpidbyname,
    // [SYS_sigprocmask]       = (void *)sys_sigprocmask,
};
