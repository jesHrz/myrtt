#ifndef __RT_SYSCALLS_H_
#define __RT_SYSCALLS_H_

#define SYS_syscall 0
#define MAX_SYSCALL 256

struct rt_syscall_struct {
    int argc;
    void *entry;
};
typedef struct rt_syscall_struct rt_syscall_struct_t;

#define __NR_restart_syscall 0
#define __NR_exit 1
#define __NR_fork 2
#define __NR_read 3
#define __NR_write 4
#define __NR_open 5
#define __NR_close 6
#define __NR_creat 8
#define __NR_link 9
#define __NR_unlink 10
#define __NR_execve 11
#define __NR_chdir 12
#define __NR_time 13
#define __NR_lseek 19
#define __NR_getpid 20
#define __NR_access 33
#define __NR_kill 37
#define __NR_rename 38
#define __NR_mkdir 39
#define __NR_signal 48
#define __NR_ioctl 54
#define __NR_fcntl 55
#define __NR_sigaction 67
#define __NR_sigsuspend 72
#define __NR_sigpending 73
#define __NR_gettimeofday 78
#define __NR_settimeofday 79
#define __NR_stat 106
#define __NR_fstat 108
#define __NR_fsync 118
#define __NR_sigreturn 119
#define __NR_sigprocmask 126
#define __NR_nanosleep 162

#define __NR_pthread_create 170
#define __NR_pthread_detach 171
#define __NR_pthread_join 172
#define __NR_pthread_self 173
#define __NR_Pthread_exit 174
#define __NR_pthread_kill 175
#define __NR_pthread_sigmask 176
#define __NR_pthread_cancel 177
#define __NR_pthread_mutexattr_init 178
#define __NR_pthread_mutexattr_destroy 179
#define __NR_pthread_mutexattr_gettype 180
#define __NR_pthread_mutexattr_settype 181
#define __NR_pthread_mutexattr_getpshared 182
#define __NR_pthread_mutexattr_setpshared 183
#define __NR_pthread_mutex_init 184
#define __NR_pthread_mutex_destroy 185
#define __NR_pthread_mutex_lock 186
#define __NR_pthread_mutex_unlock 187
#define __NR_pthread_mutex_trylock 188

#define __NR_getpidbyname 250
#define __NR_malloc 251
#define __NR_realloc 252
#define __NR_calloc 253
#define __NR_free 254
#define __NR_dlmodule_init 255

#endif // __RT_SYSCALLS_H_