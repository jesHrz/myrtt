#include "lib_syscalls.h"

long syscall_0(int nr)
{
    asm
    (
        "push {r4-r11}\n"
        "mov r12, sp\n"
    );
    register long reg8 __asm__("r8") = (long) nr;
    register long reg0 __asm__("r0") = 0;
    __asm__ __volatile__
    (
        "svc %1"
        :"=r"(reg0)
        :"i"(SYS_syscall), "r"(reg8)
        :"memory", "r11"
    );

    asm("pop {r4-r11}");
    return reg0;
}

long syscall_1(int nr, long arg1)
{
    asm
    (
        "push {r4-r11}\n"
        "mov r12, sp\n"
    );
    register long reg8 __asm__("r8") = (long) nr;
    register long reg0 __asm__("r0") = (long) arg1;
    __asm__ __volatile__
    (
        "svc %1"
        :"=r"(reg0)
        :"i"(SYS_syscall), "r"(reg8), "r"(reg0)
        :"memory", "r11"
    );

    asm("pop {r4-r11}");
    return reg0;
}

long syscall_2(int nr, long arg1, long arg2)
{
    asm
    (
        "push {r4-r11}\n"
        "mov r12, sp\n"
    );
    register long reg8 __asm__("r8") = (long) nr;
    register long reg1 __asm__("r1") = (long) arg2;
    register long reg0 __asm__("r0") = (long) arg1;
    __asm__ __volatile__
    (
        "svc %1"
        :"=r"(reg0)
        :"i"(SYS_syscall), "r"(reg8), "r"(reg0), "r"(reg1)
        :"memory", "r11"
    );

    asm("pop {r4-r11}");
    return reg0;
}

long syscall_3(int nr, long arg1, long arg2, long arg3)
{
    asm
    (
        "push {r4-r11}\n"
        "mov r12, sp\n"
    );
    register long reg8 __asm__("r8") = (long) nr;
    register long reg2 __asm__("r2") = (long) arg3;
    register long reg1 __asm__("r1") = (long) arg2;
    register long reg0 __asm__("r0") = (long) arg1;
    __asm__ __volatile__
    (
        "svc %1"
        :"=r"(reg0)
        :"i"(SYS_syscall), "r"(reg8), "r"(reg0), "r"(reg1), "r"(reg2)
        :"memory", "r11"
    );

    asm("pop {r4-r11}");
    return reg0;
}

long syscall_4(int nr, long arg1, long arg2, long arg3, long arg4)
{
    asm
    (
        "push {r4-r11}\n"
        "mov r12, sp\n"
    );
    register long reg8 __asm__("r8") = (long) nr;
    register long reg3 __asm__("r3") = (long) arg4;
    register long reg2 __asm__("r2") = (long) arg3;
    register long reg1 __asm__("r1") = (long) arg2;
    register long reg0 __asm__("r0") = (long) arg1;
    __asm__ __volatile__
    (
        "svc %1"
        :"=r"(reg0)
        :"i"(SYS_syscall), "r"(reg8), "r"(reg0), "r"(reg1), "r"(reg2), "r"(reg3)
        :"memory", "r11"
    );

    asm("pop {r4-r11}");
    return reg0;
}
