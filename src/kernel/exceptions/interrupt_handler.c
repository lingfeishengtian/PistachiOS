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

void dump_cpu_state(interrupt_handler_t* register_struct){
    uint8_t targetStrLen = 15;

    for (uint8_t i = 0; i < 6; i++)
    {
       for (uint8_t j = 0; j < 5; j++)
       {
            uint8_t reg_ind = i * 5 + j;
            bool is_two_digit = reg_ind >= 10;
            
            uint8_t padLen = targetStrLen - (1 + (is_two_digit ? 2 : 1) + 4 + 8);
            if(padLen < 0) padLen = 0;

            printf("|x%d: 0x%08x%*.*s| ", reg_ind, *((uint64_t*) ((char*) register_struct + reg_ind * 8)), padLen, padLen, " ");
       }
       printf("\n");
    }
    printf("|x%d: 0x%08x|\n",  30, *((uint64_t*) ((char*) register_struct + 30 * 8)));
}

void interrupt_handler(uint64_t type, uint64_t ESR, uint64_t ELR, interrupt_handler_t* register_struct){
    int level = (type + 1) / 4;
    int eType = (type + 1) % 4;

    printf("CPU Dump\n");
    dump_cpu_state(register_struct);

    if(type == IRQ_EL1h || type == IRQ_EL1t || type == IRQ_EL0_32 || type == IRQ_EL0_64){
        handle_irq();
    }
}

void enable_interrupt_controller()
{
    kput32(ENABLE_IRQS_1, SYSTEM_TIMER_IRQ_1);
}