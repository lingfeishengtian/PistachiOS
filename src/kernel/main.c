#include "standard_types.h"
#include "kernel/peripherals/mini_uart.h"
#include "utils/printf.h"

void _putchar(char c){
    uart_putchar(c);
}

void init_debug_utils(){
    init_uart();
}

void kernel_main(){
    printf("Number: %0.4f", 5.234252334);

    // Accept input
    while (1) {
        uart_putchar(uart_getchar());
    }
    return;
}