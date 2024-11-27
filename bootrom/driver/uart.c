#include "uart.h"
#include <asm/mmio.h>


void uart_putc(char ch)
{
	while ((readl(UART_LSR_OFFSET) & UART_LSR_THRE) == 0)
		;

	writel(UART_THR_OFFSET, ch);
}

int uart_getc(void)
{
	if (readl(UART_LSR_OFFSET) & UART_LSR_DR)
		return readl(UART_RBR_OFFSET);
	return -1;
}
void uart_puts(char* str)
{
	while (*str != '\0')
		uart_putc(*str++);
}

void uart_init()
{
	register int bdiv asm ("t0");
	//writel(0xd002c,2);
	writel(0xd0108,0x1f);
	writel(0xd0114,0x1f);
	//writel(0xd0008,0x24);
	writel(0xd0028,0x30000);
	writel(0xd0008,0x22);
	bdiv = (UART_CLK + 8*UART_DEFAULT_BAUD) /
		(16 * UART_DEFAULT_BAUD);

	/* Disable all interrupts */
	writel(UART_IER_OFFSET, 0x00);
	/* Enable DLAB */
	writel(UART_LCR_OFFSET, 0x80);

	if (bdiv) {
		/* Set divisor low byte */
		writel(UART_DLL_OFFSET, bdiv & 0xff);
		/* Set divisor high byte */
		writel(UART_DLM_OFFSET, (bdiv >> 8) & 0xff);
	}

	/* 8 bits, no parity, one stop bit */
	writel(UART_LCR_OFFSET, 0x03);
	/* Enable FIFO */
	writel(UART_FCR_OFFSET, 0x01);
	/* No modem control DTR RTS */
	writel(UART_MCR_OFFSET, 0x00);
	/* Clear line status */
	readl(UART_LSR_OFFSET);
	/* Read receive buffer */
	readl(UART_RBR_OFFSET);
	/* Set scratchpad */
	writel(UART_SCR_OFFSET, 0x00);

	while(1){
	   writel(UART_BASE + 0, 0x5a);
	   for(bdiv=0x0; bdiv<0x100;bdiv++){}
	   //writel(UART_BASE + 0, '\n');
	}
}
