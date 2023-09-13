#include "uart.h"
#include <asm/mmio.h>

#define UART_CLK          50000000
#define UART_DEFAULT_BAUD 115200

static void uart_delay(unsigned int loops)
{
	while(loops--){
		__asm__ volatile ("nop");
	}
}

void uart_putc(char c)
{
	unsigned int value;
	
	value = readl(LSR);
	while(!(value & 0x60)){
		uart_delay(100);
		value = readl(LSR);
	}

	writel(THR, c);
}

void uart_puts(char* str)
{
	while (*str != '\0')
		uart_putc(*str++);
}

void uart_init()
{
	unsigned int divisor = UART_CLK / (16 * UART_DEFAULT_BAUD);

	writel(LCR, 0x83);
	
	while(readl(USR) & 0x1);

	writel(DLH, 0);
	writel(DLL, divisor);
	writel(LCR, 0x03);
	writel(FCR, 0x01);
	writel(IER, 0);
	writel(MCR, (RTS | DTR));
}
