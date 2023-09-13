#include <uart.h>
#include <asm/mmio.h>

#define UART_DEFAULT_BAUD  115200

void uart_putc(char c)
{
	while((readb(UART_LSR) & UART_LSR_EMPTY) == 0);

	writeb(UART_DAT, c);
}

void uart_puts(char *str)
{
	while (*str != '\0')
		uart_putc(*str++);
}

void uart_init(void)
{
	unsigned int uart16550_clock = 1843200;
	unsigned int divisor = uart16550_clock / (16 * UART_DEFAULT_BAUD);

	writeb(UART_IER, 0);

	writeb(UART_LCR, 0x80);
	writeb(UART_DLL, (unsigned char)divisor);
	writeb(UART_DLM, (unsigned char)(divisor >> 8));
	writeb(UART_LCR, 0x3);
	writeb(UART_FCR, 0xc7);
}
