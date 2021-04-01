#ifndef P_OS_KERNEL_EXCEPTIONS_INTERRUPTS_H
#define P_OS_KERNEL_EXCEPTIONS_INTERRUPTS_H

#include "kernel/peripherals/base.h"

#define REGISTER_SIZES  256

#define SYNC_EL1t		0 
#define IRQ_EL1t		1 
#define FIQ_EL1t		2 
#define ERROR_EL1t		3 

#define SYNC_EL1h		4 
#define IRQ_EL1h		5 
#define FIQ_EL1h		6 
#define ERROR_EL1h		7 

#define SYNC_EL0_64	    8 
#define IRQ_EL0_64	    9 
#define FIQ_EL0_64		10 
#define ERROR_EL0_64	11 

#define SYNC_EL0_32		12 
#define IRQ_EL0_32		13 
#define FIQ_EL0_32		14 
#define ERROR_EL0_32	15 

#define IRQ_BASIC_PENDING	(P_BASE + 0x0000B200)
#define IRQ_PENDING_1		(P_BASE + 0x0000B204)
#define IRQ_PENDING_2		(P_BASE + 0x0000B208)
#define FIQ_CONTROL		    (P_BASE + 0x0000B20C)
#define ENABLE_IRQS_1		(P_BASE + 0x0000B210)
#define ENABLE_IRQS_2		(P_BASE + 0x0000B214)
#define ENABLE_BASIC_IRQS	(P_BASE + 0x0000B218)
#define DISABLE_IRQS_1		(P_BASE + 0x0000B21C)
#define DISABLE_IRQS_2		(P_BASE + 0x0000B220)
#define DISABLE_BASIC_IRQS	(P_BASE + 0x0000B224)

#define SYSTEM_TIMER_IRQ_0	(1 << 0)
#define SYSTEM_TIMER_IRQ_1	(1 << 1)
#define SYSTEM_TIMER_IRQ_2	(1 << 2)
#define SYSTEM_TIMER_IRQ_3	(1 << 3)

#endif /* P_OS_KERNEL_EXCEPTIONS_EXCEPTION_TYPES_H */
