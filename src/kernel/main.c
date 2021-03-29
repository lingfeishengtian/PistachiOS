#include "standard_types.h"
#include "kernel/peripherals/mini_uart.h"

void kernel_main(){
    init_uart();
    uart_printf("Test");

    while (1) {
        uart_putchar(uart_getchar());
    }
    return;
}