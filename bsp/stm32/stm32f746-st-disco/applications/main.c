/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-01-06     jinsheng   first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>

/* defined the LED1 pin: PI1 */
#define LED1_PIN    GET_PIN(I, 1)

int main(void)
{
    __asm__ __volatile__
    (
        "svc #11"
    );

    return RT_EOK;
}
