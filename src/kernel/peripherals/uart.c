#include "kernel/peripherals/uart.h"
#include "kernel/peripherals/base.h"
#include "utils/printf.h"
#include "utils/utils.h"

void uart0_putchar(char character)
{
	while(1) {
		if(!(kget32(UART0_FLAG) & WRITE_DATA_RDY_UART0)) 
			break;
	}

	kput32(UART0_DATA,character);
}

char uart0_getchar()
{
	while(1) {
		if(!(kget32(UART0_FLAG) & READ_DATA_RDY_UART0)) 
			break; 
	}

	return(kget32(UART0_DATA) & 0xFF);
}

void init_uart0()
{
	uint32_t selector;

	selector = kget32(GPFSEL1);
	selector &= ~(7<<12);                   // clean gpio14
	selector |= 4<<12;                      // set alt5 for gpio14
	selector &= ~(7<<15);                   // clean gpio15
	selector |= 4<<15;                      // set alt5 for gpio15
	kput32(GPFSEL1,selector);

	kput32(GPPUD,0);
	kdelay(150);
	kput32(GPPUDCLK0, (1<<14)|(1<<15));
	kdelay(150);
	kput32(GPPUDCLK0,0);

	kput32(UART0_IBRD,UART0_IBRD_115200);   // Set baud rate.
	kput32(UART0_FBRD,UART0_FBRD_115200);
	kput32(UART0_LCRH, (7 << 4)); 			//Set RTS line to be always high

	kput32(UART0_CONTROL, (1 << 0) | (3 << 8));               //Finally, enable transmitter and receiver
}