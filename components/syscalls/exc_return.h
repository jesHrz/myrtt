#ifndef __ARCH_ARM_CORTEXM7_EXC_RETURN_H_
#define __ARCH_ARM_CORTEXM7_EXC_RETURN_H_

#define RT_THREAD_MSP                   (0)
#define RT_THREAD_PSP                   (1 << 0)
#define RT_THREAD_HANDLER               (0)
#define RT_THREAD_THREAD                (1 << 1)

#define RT_THREAD_HANDLER_MSP           (RT_THREAD_HANDLER | RT_THREAD_MSP)
#define RT_THREAD_HANDLER_PSP           (RT_THREAD_HANDLER | RT_THREAD_PSP)   // illegal status
#define RT_THREAD_THREAD_MSP            (RT_THREAD_THREAD | RT_THREAD_MSP)
#define RT_THREAD_THREAD_PSP            (RT_THREAD_THREAD | RT_THREAD_PSP)

#define RT_THREAD_LR_MASK               (RT_THREAD_THREAD_PSP << 2)

#define KSP_OFFSET          0x00
#define USP_OFFSET          0x04
#define LR_OFFSET           0x08

#define EXC_RETURN_BASE             0xffffffe1
#define EXC_RETURN_PROCESS_STACK    (1 << 2)
#define EXC_RETURN_THREAD_MODE      (1 << 3)
#define EXC_RETURN_USE_FPU          (1 << 4)

#endif //__ARCH_ARM_CORTEXM7_EXC_RETURN_H_