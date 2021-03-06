.cpu cortex-m7
.syntax unified
.thumb
.text

.global rt_thread_exit

.global SVC_Handler
.type SVC_Handler, % function
SVC_Handler:
    push {lr}
    bl rt_thread_exit
    pop {pc}