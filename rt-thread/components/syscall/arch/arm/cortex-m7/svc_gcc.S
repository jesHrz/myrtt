#include <exc_return.h>
#include "svc_gcc.h"

.cpu cortex-m7
.syntax unified
.thumb
.text

.global rt_thread_self

.global SVC_Handler
.type SVC_Handler, % function
SVC_Handler:
    AND   r12, lr,  #RT_THREAD_LR_MASK
    LSR   r12, r12, #2                /* r12=(lr&0x0C)>>2 */
    TST   r12, #RT_THREAD_PSP
    MRSNE r12, psp
    MRSEQ r12, msp   

    CMP   r8, #0
    BLT   svc_exit
    CMP   r8, #NR_SVCALL
    BGT   svc_exit

    LSL   r8, #2

    PUSH  {lr}
    LDR   r11, =svcall_table
    LDR   r11, [r11, r8]
    BLX   r11

    STR   r0, [r12]
    POP   {lr}

svc_exit:
    MOV   r8, #-88  // return -ENOSYS
    STR   r8, [r12]
    BX    lr