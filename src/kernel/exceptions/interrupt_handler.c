#include "kernel/exceptions/interrupts.h"
#include "kernel/exceptions/interrupt_handler.h"
#include "kernel/timer.h"
#include "utils/utils.h"
#include "utils/printf.h"

void handle_irq(){
    uint32_t irq = kget32(IRQ_PENDING_1);

    switch (irq)
    {
    case (SYSTEM_TIMER_IRQ_1):
        handle_timer_int();
        break;
    
    default:
        break;
    }
}

void interrupt_handler(uint64_t type, uint64_t ESR, uint64_t ELR, interrupt_handler_t* register_struct){
    int level = (type + 1) / 4;
    int eType = (type + 1) % 4;

    printf("CPU Dump: 0x%x\n", register_struct->x30);

    if(type == IRQ_EL1h || type == IRQ_EL1t || type == IRQ_EL0_32 || type == IRQ_EL0_64){
        handle_irq();
    }
}

void enable_interrupt_controller()
{
    kput32(ENABLE_IRQS_1, SYSTEM_TIMER_IRQ_1);
}