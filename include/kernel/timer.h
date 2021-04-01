#ifndef P_OS_INCLUDE_KERNEL_TIMER_H
#define P_OS_INCLUDE_KERNEL_TIMER_H

#include "kernel/peripherals/base.h"

#define TIMER_CS        (P_BASE + 0x00003000)
#define TIMER_CLO       (P_BASE + 0x00003004)
#define TIMER_CHI       (P_BASE + 0x00003008)
#define TIMER_C0        (P_BASE + 0x0000300C)
#define TIMER_C1        (P_BASE + 0x00003010)
#define TIMER_C2        (P_BASE + 0x00003014)
#define TIMER_C3        (P_BASE + 0x00003018)

#define TIMER_CS_M0	(1 << 0)
#define TIMER_CS_M1	(1 << 1)
#define TIMER_CS_M2	(1 << 2)
#define TIMER_CS_M3	(1 << 3)

void timer_init();
void handle_timer_int();

#endif /* P_OS_INCLUDE_KERNEL_TIMER_H */
