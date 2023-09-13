#ifndef	_UART_H
#define	_UART_H

#define UART_BASE 0x310B0000

#define SYNC_ADDR UART_BASE + 0xbc

#define RBR       UART_BASE + 0x00
#define THR       UART_BASE + 0x00
#define DLL       UART_BASE + 0x00
#define DLH       UART_BASE + 0x04
#define IER       UART_BASE + 0x04
#define IIR       UART_BASE + 0x08
#define FCR       UART_BASE + 0x08
#define LCR       UART_BASE + 0x0c
#define MCR       UART_BASE + 0x10
#define LSR       UART_BASE + 0x14
#define MSR       UART_BASE + 0x18
#define SCR_UART  UART_BASE + 0x1c
#define LPDLL     UART_BASE + 0x20
#define LPDLH     UART_BASE + 0x24
#define USR       UART_BASE + 0x7c
#define HTX       UART_BASE + 0xa4
#define DMASA     UART_BASE + 0xa8
#define UCV       UART_BASE + 0xf8
#define CTR       UART_BASE + 0xfc

#define RFE  0x80
#define TEMT 0x40
#define THRE 0x20
#define BI   0x10
#define FE   0X08
#define PE   0X04
#define OE   0X02
#define DR   0X01
#define DTR  0X01
#define RTS  0X02
#define AFCE 0X20
#define SIRE 0X40
#define CTS  0X10

void uart_init(void);
void uart_putc(char c);
void uart_puts(char* str);

void print_hart_info(unsigned int hart);
void print_downloading_info(unsigned int from, unsigned int to, unsigned int size);

#endif  /*_UART_H */
