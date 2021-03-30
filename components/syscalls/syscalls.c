#include <syscalls.h>
#include <rtthread.h>
#include <rtdef.h>

#ifdef RT_USING_DFS
#include <dfs_posix.h>
#endif

#ifdef RT_USING_MODULE
#include <dlmodule.h>
#endif

#ifdef RT_USING_PTHREAD
#include <pthread.h>
#include "pthread.h"
#endif

/* ************* syscall service entry ***************** */
int sys_unimplemented()
{
    return -ENOSYS;
}

void _exit(int rc)
{
#ifdef RT_USING_MODULE
    rt_thread_t tid = rt_thread_self();
    struct rt_dlmodule* module = (struct rt_dlmodule*)tid->module_id;
    if (module != RT_NULL && module->main_thread == tid)
        dlmodule_exit(module);
#endif
    rt_thread_exit();
}

int _close(int file)
{
    if (file >= 0 && file <= 2)
    {
        *_rt_errno() = EBADF;
        return -1;
    }
#ifdef RT_USING_POSIX
    return close(file);
#endif
}

int
nanosleep (const struct timespec *rqtp,
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
settimeofday (struct timeval *tp,
                  struct timeval *tzp)
{
    return -ENOSYS;
}

int
getpidbyname(const char *name)
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

#undef SYSCALL_VOID_1
#define SYSCALL_VOID_1(name, service, nr, tp1)\
RT_WEAK int sys_##name(int arg1)\
{\
    service((tp1)arg1);\
    return 0;\
}

#undef SYSCALL_0
#define SYSCALL_0(name, service, nr) \
RT_WEAK int sys_##name() \
{\
    return (int)service();\
}

#undef SYSCALL_1
#define SYSCALL_1(name, service, nr, tp1) \
RT_WEAK int sys_##name(int arg1) \
{\
    return (int)service((tp1)arg1);\
}

#undef SYSCALL_2
#define SYSCALL_2(name, service, nr, tp1, tp2) \
RT_WEAK int sys_##name(int arg1, int arg2) \
{\
    return (int)service((tp1)arg1, (tp2)arg2);\
}

#undef SYSCALL_3
#define SYSCALL_3(name, service, nr, tp1, tp2, tp3) \
RT_WEAK int sys_##name(int arg1, int arg2, int arg3) \
{\
    return (int)service((tp1)arg1, (tp2)arg2, (tp3)arg3);\
}

#undef SYSCALL_4
#define SYSCALL_4(name, service, nr, tp1, tp2, tp3, tp4) \
RT_WEAK int sys_##name(int arg1, int arg2, int arg3, int arg4) \
{\
    return (int)service((tp1)arg1, (tp2)arg2, (tp3)arg3, (tp4)arg4);\
}

#include "syscall_construct.h"
/* ************* ************************ ***************** */



rt_syscall_struct_t syscall_table[MAX_SYSCALL] = { 
    [0 ... (MAX_SYSCALL - 1)] = {0, (void *)&sys_unimplemented}
};

#undef SYSCALL_VOID_1
#define SYSCALL_VOID_1(name, service, nr, tp1) SYSCALL_1(name, service, nr, tp1)

#undef SYSCALL_0
#define SYSCALL_0(name, service, nr) \
if (add_syscall_entry((void *)&(sys_##name), 0, nr))  \
    return 1;    

#undef SYSCALL_1
#define SYSCALL_1(name, service, nr, tp1) \
if (add_syscall_entry((void *)&(sys_##name), 1, nr))  \
    return 1;    

#undef SYSCALL_2
#define SYSCALL_2(name, service, nr, tp1, tp2) \
if (add_syscall_entry((void *)&(sys_##name), 2, nr))  \
    return 1;    

#undef SYSCALL_3
#define SYSCALL_3(name, service, nr, tp1, tp2, tp3) \
if (add_syscall_entry((void *)&(sys_##name), 3, nr))  \
    return 1;    

#undef SYSCALL_4
#define SYSCALL_4(name, service, nr, tp1, tp2, tp3, tp4) \
if (add_syscall_entry((void *)&(sys_##name), 4, nr))  \
    return 1;    

static int add_syscall_entry(void *entry, int argc, int nr)
{
    if (nr < 0 || nr >= MAX_SYSCALL)
        return 1;

    if (syscall_table[nr].entry != (void *)&sys_unimplemented)
        return 1;

    syscall_table[nr].argc  = argc;
    syscall_table[nr].entry = entry;
    return 0;
}

int syscall_init()
{
    #include "syscall_construct.h"

    return 0;
}
INIT_COMPONENT_EXPORT(syscall_init);