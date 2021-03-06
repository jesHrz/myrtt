#ifndef __RT_SYSCALL_H_
#define __RT_SYSCALL_H_

typedef void (*rt_fn_ptr)(void);

rt_fn_ptr sys_call_table[];

#endif // __RT_SYSCALL_H_