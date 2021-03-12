#include <exc_return.h>
#include <syscall.h>

.cpu cortex-m7
.syntax unified
.thumb
.text

.global do_syscall

.global SVC_Handler
.type SVC_Handler, % function
SVC_Handler:
    PUSH {r1, r2}
    MRS  r1, psp
    MRS  r2, psp

#if defined (__VFP_FP__) && !defined(__SOFTFP__)
    TST     lr, #0x10           /* if(!EXC_RETURN[4]) */
    VSTMDBEQ r1!, {d8 - d15}    /* push FPU register s16~s31 */
#endif

    STMFD   r1!, {r4-r11}

#if defined (__VFP_FP__) && !defined(__SOFTFP__)
    MOV     r0, #0x00           /* flag = 0 */

    TST     lr, #0x10           /* if(!EXC_RETURN[4]) */
    MOVEQ   r0, #0x01           /* flag = 1 */

    STMFD   r1!, {r0}           /* push flag */
#endif
    MSR  psp, r1
    MOV r4, r1
    MOV r5, r2
    POP {r1, r2}

    LDR r0, [r5, #0x1c]             // r0: psp + 0x00
                                    // r1: psp + 0x04
                                    // r2: psp + 0x08
                                    // r3: psp + 0x0c
                                    // r12: psp + 0x10
                                    // lr: psp + 0x14
                                    // pc: psp + 0x18
                                    // psr: psp + 0x1c
    PUSH {r0}   // push psr

    LDR  r0, =syscall_in_thread
    PUSH {r0}   // push pc
    LDR  r0, [r5, #0x14]
    PUSH {r0}   // push lr
    PUSH {r12}
    PUSH {r3}
    PUSH {r2}
    PUSH {r1}
    PUSH {r4}

    MRS  r0, CONTROL
    BIC  r0, 0x01
    MSR  CONTROL, r0

    BIC  lr, #EXC_RETURN_PROCESS_STACK
    BX   lr

.global syscall_in_thread
.type syscall_in_thread, % function
syscall_in_thread:
    BL  do_syscall
    MOV r4, r0

    LDMFD r4!, {r0-r3,r12}
    LDMFD r4!, {lr}
    LDMFD r4!, {r6}
    LDMFD r4!, {r5}
    ADD r4, #4
    MSR psp, r4
    MSR psr, r5

    MRS r4, CONTROL
    ORR r4, 0x03
    MSR CONTROL, r4

    ORR r6, 0x01
    BX r6