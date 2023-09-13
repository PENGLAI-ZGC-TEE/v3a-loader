#ifndef	_UART_H
#define	_UART_H

#define UART        0x10000000

#define UART_DAT    (UART + 0x00)
#define UART_IER    (UART + 0x01)
#define UART_IIR    (UART + 0x02)
#define UART_FCR    (UART + 0x02)
#define UART_LCR    (UART + 0x03)
#define UART_MCR    (UART + 0x04)
#define UART_LSR    (UART + 0x05)
#define UART_MSR    (UART + 0x06)

#define UART_DLL (UART + 0x00)
#define UART_DLM (UART + 0x01)

#define UART_LSR_ERROR      0x80
#define UART_LSR_EMPTY      0x40
#define UART_LSR_TFE	    0x20
#define UART_LSR_BI	    0x10
#define UART_LSR_FE	    0x08
#define UART_LSR_PE	    0x04
#define UART_LSR_OE	    0x02
#define UART_LSR_DR	    0x01

void uart_init(void);
void uart_putc(char c);
void uart_puts(char* str);

int print(const char *fmt, ...);

void print_info(unsigned int hart_id);

#endif
