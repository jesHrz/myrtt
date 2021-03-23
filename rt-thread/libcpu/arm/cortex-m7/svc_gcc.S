#include <exc_return.h>
#include <syscall.h>

.cpu cortex-m7
.syntax unified
.thumb
.text

.global syscall_dispatch
.global rt_hw_context_switch_to

.global SVC_Handler
.type SVC_Handler, % function
SVC_Handler:
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
    MOV r4, r1                  // r4 = new psp
    MOV r5, r2                  // r5 = old psp

    /* make msp 8-byte aligned */
    MOV r0, sp
    BIC r0, #7
    MOV sp, r0
    /* construct exception stack frame */
    MOV r0, #0x01000000
    PUSH {r0}   // psr
    LDR r0, =_do_syscall
    PUSH {r0}   // pc
    LDR  r0, [r5, #0x14]
    PUSH {r0}   // lr
    PUSH {r12}  // r12
    PUSH {r3}   // r3
    PUSH {r2}   // r2
    PUSH {r1}   // r1
    PUSH {r1}   // r0 - should be $psp as parameter

    /* switch to privileged thread-mode */
    MRS  r0, CONTROL
    BIC  r0, 0x01
    MSR  CONTROL, r0

    BIC  lr, #EXC_RETURN_PROCESS_STACK
    BX   lr  // jump to _do_syscall

_do_syscall:
    BL syscall_dispatch
    BL rt_hw_context_switch_to  /* go back to user-mode */

    /* never reach here */
1:  B  1b