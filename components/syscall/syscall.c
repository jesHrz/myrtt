#include <syscall.h>
#include <rtthread.h>

#define SYSCALL_ENTRY(__fn) (rt_fn_ptr)(__fn)

extern void rt_thread_exit();

static void rt_sys_exit()
{
    rt_thread_exit();
}

rt_fn_ptr sys_call_table[] = {
    SYSCALL_ENTRY(rt_sys_exit)
};