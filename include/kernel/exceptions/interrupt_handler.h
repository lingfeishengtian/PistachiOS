#ifndef P_OS_KERNEL_EXCEPTIONS_INTERRUPT_HANDLER_H
#define P_OS_KERNEL_EXCEPTIONS_INTERRUPT_HANDLER_H

#include "standard_types.h"

extern void irq_vector_init();
extern void unmask_irq();
extern void mask_irq();

typedef struct __attribute__((packed))
{
    uint64_t x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30;
} interrupt_handler_t;

void interrupt_handler(uint64_t type, uint64_t ESR, uint64_t ELR, interrupt_handler_t* register_struct);
void enable_interrupt_controller();

#endif /* P_OS_KERNEL_EXCEPTIONS_INTERRUPT_HANDLER_H */
