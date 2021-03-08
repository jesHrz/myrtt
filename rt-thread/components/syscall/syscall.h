#ifndef __RT_SYSCALL_H_
#define __RT_SYSCALL_H_

#define NR_SVCAL                            19

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
#define SYS_msgget                          15
#define SYS_msgsend                         16
#define SYS_msgrcv                          17
#define SYS_log                             18

#endif // __RT_SYSCALL_H_