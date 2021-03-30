#include "kernel/peripherals/uart.h"
#include "kernel/peripherals/base.h"
#include "utils/printf.h"
#include "utils/utils.h"

void uart0_putchar(char character)
{
	while(1) {
		int a = kget32(UART0_FR);
		printf("%d\n", a);
		if(a & (1 << 5) ) 
			break;
	}

	kput32(UART0_DR,character);
}

char uart0_getchar()
{
	while(1) {
		if(kget32(UART0_FR) & (1 << 4) ) 
			break;
	}
	return(kget32(UART0_DR) & 0xFF);
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

	kput32(UART0_CR,0);                  	 // Disable UART0

	kput32(GPPUD,0);
	kdelay(150);
	kput32(GPPUDCLK0,(1<<14)|(1<<15));
	kdelay(150);
	kput32(GPPUDCLK0,0);

	kput32(UART0_ICR, 0x7FF);

	kput32(UART0_IBRD,UART0_IBRD_115200);    // Set baud rate.
	kput32(UART0_FBRD,UART0_FBRD_115200);
	kput32(UART0_LCRH, (3 << 5) | (1 << 4)); //Set RTS line to be always high
	kput32(UART0_IMSC, (1 << 1) | (1 << 4) | (1 << 5) | (1 << 6) |
	                       (1 << 7) | (1 << 8) | (1 << 9) | (1 << 10));

	kput32(UART0_CR, (1 << 0) | (1 << 8) | (1 << 9));               //Finally, enable transmitter and receiver
}