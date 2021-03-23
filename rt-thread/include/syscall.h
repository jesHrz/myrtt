#ifndef __RT_SYSCALL_H_
#define __RT_SYSCALL_H_

#define NR_SYSCALL                          29

#define SYS_syscall                         0

#define SYS_exit                            0
#define SYS_read                            1
#define SYS_write                           2
#define SYS_lseek                           3
#define SYS_open                            4
#define SYS_close                           5
#define SYS_rename                          6
#define SYS_stat                            7
#define SYS_fstat                           8
#define SYS_fsync                           9
#define SYS_fcntl                           10
#define SYS_ioctl                           11
#define SYS_nanosleep                       12
#define SYS_gettimeofday                    13
#define SYS_settimeofday                    14
#define SYS_errno                           15
#define SYS_mkdir                           16
#define SYS_unlink                          17
#define SYS_malloc                          18
#define SYS_realloc                         19
#define SYS_calloc                          20
#define SYS_free                            21
#define SYS_dlmodule_init                   22
#define SYS_dlmodule_cleanup                23
#define SYS_signal                          24
#define SYS_kill                            25
#define SYS_sigreturn                       26
#define SYS_getpid                          27
#define SYS_getpidbyname                    28

#endif // __RT_SYSCALL_H_