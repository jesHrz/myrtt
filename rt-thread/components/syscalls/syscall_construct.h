#include <syscalls.h>
#include <pthread.h>

SYSCALL_VOID_1(exit, _syscall_exit, __NR_exit, int)

SYSCALL_2(nanosleep, nanosleep, __NR_nanosleep, const struct timespec*, struct timespec*)
SYSCALL_2(settimeofday, settimeofday, __NR_settimeofday, const struct timeval*, const struct timezone*)


#ifdef RT_USING_POSIX
SYSCALL_3(read, read, __NR_read, int, void*, size_t)
SYSCALL_3(write, write, __NR_write, int, const void*, size_t)
SYSCALL_3(open, open, __NR_open, const char*, int, int)
SYSCALL_1(close, _syscall_close, __NR_close, int)
SYSCALL_1(unlink, unlink, __NR_unlink, const char*)
SYSCALL_3(lseek, lseek, __NR_lseek, int, off_t, int)

SYSCALL_2(rename, rename, __NR_rename, const char*, const char*)
SYSCALL_2(mkdir, mkdir, __NR_mkdir, const char*, int)
SYSCALL_3(ioctl, ioctl, __NR_ioctl, int, unsigned long, void*)
SYSCALL_3(fcntl, fcntl, __NR_fcntl, int, int, void*)
SYSCALL_2(gettimeofday, gettimeofday, __NR_gettimeofday, struct timeval*, struct timezone*)
SYSCALL_2(stat, stat, __NR_stat, const char *, struct stat*)
SYSCALL_2(fstat, fstat, __NR_fstat, int, struct stat*)
SYSCALL_1(fsync, fsync, __NR_fsync, int)
#endif

#ifdef RT_USING_SIGNALS
SYSCALL_2(kill, sys_kill, __NR_kill, rt_thread_t, int)
SYSCALL_2(signal, sys_signal, __NR_signal, int, rt_sighandler_t)
SYSCALL_0(sigreturn, sys_sigreturn, __NR_sigreturn)
SYSCALL_3(sigprocmask, sys_sigprocmask, __NR_sigprocmask, int, const sigset_t*, sigset_t*)
SYSCALL_3(sigaction, sys_sigaction, __NR_sigaction, int, const struct sigaction*, struct sigaction*)
#endif

SYSCALL_0(getpid, rt_thread_self, __NR_getpid)
SYSCALL_1(malloc, rt_malloc, __NR_malloc, size_t)
SYSCALL_2(realloc, rt_realloc, __NR_realloc, void*, size_t)
SYSCALL_2(calloc, rt_calloc, __NR_calloc, size_t, size_t)
SYSCALL_VOID_1(free, rt_free, __NR_free, void*)
SYSCALL_1(getpidbyname, getpidbyname, __NR_getpidbyname, const char*)

#ifdef RT_USING_MODULE
SYSCALL_2(dlmodule_init, dlmodule_init, __NR_dlmodule_init, int*, char**)
#endif

#ifdef RT_USING_PTHREADS
SYSCALL_4(pthread_create, pthread_create, __NR_pthread_create, pthread_t*, const pthread_attr_t*, void*(*)(void*), void*)
SYSCALL_1(pthread_detach, pthread_detach, __NR_pthread_detach, pthread_t)
SYSCALL_2(pthread_join, pthread_join, __NR_pthread_join, pthread_t, void**)
SYSCALL_0(pthread_self, pthread_self, __NR_pthread_self)
SYSCALL_VOID_1(pthread_exit, pthread_exit, __NR_Pthread_exit, void*)
SYSCALL_2(pthread_kill, pthread_kill, __NR_pthread_kill, pthread_t, int)
SYSCALL_3(pthread_sigmask, pthread_sigmask, __NR_pthread_sigmask, int, const sigset_t*, sigset_t*)
SYSCALL_1(pthread_cancel, pthread_cancel, __NR_pthread_cancel, pthread_t)

SYSCALL_1(pthread_mutexattr_init, pthread_mutexattr_init, __NR_pthread_mutexattr_init, pthread_mutexattr_t*)
SYSCALL_1(pthread_mutexattr_destroy, pthread_mutexattr_destroy, __NR_pthread_mutexattr_destroy, pthread_mutexattr_t*)
SYSCALL_2(pthread_mutexattr_gettype, pthread_mutexattr_gettype, __NR_pthread_mutexattr_gettype, pthread_mutexattr_t*, int*)
SYSCALL_2(pthread_mutexattr_settype, pthread_mutexattr_settype, __NR_pthread_mutexattr_settype, pthread_mutexattr_t*, int)
SYSCALL_2(pthread_mutexattr_getpshared, pthread_mutexattr_getpshared, __NR_pthread_mutexattr_getpshared, pthread_mutexattr_t*, int*)
SYSCALL_2(pthread_mutexattr_setpshared, pthread_mutexattr_setpshared, __NR_pthread_mutexattr_setpshared, pthread_mutexattr_t*, int)

SYSCALL_2(pthread_mutex_init, pthread_mutex_init, __NR_pthread_mutex_init, pthread_mutex_t*, const pthread_mutexattr_t*)
SYSCALL_1(pthread_mutex_destroy, pthread_mutex_destroy, __NR_pthread_mutex_destroy, pthread_mutex_t*)
SYSCALL_1(pthread_mutex_lock, pthread_mutex_lock, __NR_pthread_mutex_lock, pthread_mutex_t*)
SYSCALL_1(pthread_mutex_unlock, pthread_mutex_unlock, __NR_pthread_mutex_unlock, pthread_mutex_t*)
SYSCALL_1(pthread_mutex_trylock, pthread_mutex_trylock, __NR_pthread_mutex_trylock, pthread_mutex_t*)

#endif