#include "kernel/peripherals/mini_uart.h"
#include "kernel/peripherals/base.h"
#include "utils/utils.h"

void uart_putchar(char character)
{
	while(1) {
		if(kget32(AUX_MU_LSR_REG) & WRITE_DATA_RDY) 
			break;
	}
	kput32(AUX_MU_IO_REG,character);
}

char uart_getchar()
{
	while(1) {
		if(kget32(AUX_MU_LSR_REG) & READ_DATA_RDY) 
			break;
	}
	return(kget32(AUX_MU_IO_REG)&0xFF);
}

void uart_print(char* str, ...)
{
	for (int i = 0; str[i] != '\0'; i ++) {
		uart_putchar((char)str[i]);
	}
}

void init_uart()
{
	unsigned int selector;

	selector = kget32(GPFSEL1);
	selector &= ~(7<<12);                   // clean gpio14
	selector |= 2<<12;                      // set alt5 for gpio14
	selector &= ~(7<<15);                   // clean gpio15
	selector |= 2<<15;                      // set alt5 for gpio15
	kput32(GPFSEL1,selector);

	kput32(GPPUD,0);
	kdelay(150);
	kput32(GPPUDCLK0,(1<<14)|(1<<15));
	kdelay(150);
	kput32(GPPUDCLK0,0);

	kput32(AUX_ENABLES,1);                   //Enable mini uart (this also enables access to its registers)
	kput32(AUX_MU_CNTL_REG,0);               //Disable auto flow control and disable receiver and transmitter (for now)
	kput32(AUX_MU_IER_REG,0);                //Disable receive and transmit interrupts
	kput32(AUX_MU_LCR_REG,3);                //Enable 8 bit mode
	kput32(AUX_MU_MCR_REG,0);                //Set RTS line to be always high
	kput32(AUX_MU_BAUD_REG,270);             //Set baud rate to 115200

	kput32(AUX_MU_CNTL_REG,3);               //Finally, enable transmitter and receiver
}