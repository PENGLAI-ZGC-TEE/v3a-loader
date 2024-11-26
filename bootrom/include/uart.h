#ifndef	_UART_H
#define	_UART_H

#define UART_CLK          50000000
//#define UART_CLK          24000000
//#define UART_CLK          100000000
#define UART_DEFAULT_BAUD 115200
//#define UART_BASE 0x310B0000
#define UART_BASE 0x50000

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

#define REG_SHIFT               0x2
#define UART_RBR_OFFSET		(UART_BASE + (0 << REG_SHIFT))	/* In:  Recieve Buffer Register */
#define UART_THR_OFFSET		(UART_BASE + (0 << REG_SHIFT))	/* Out: Transmitter Holding Register */
#define UART_DLL_OFFSET		(UART_BASE + (0 << REG_SHIFT))	/* Out: Divisor Latch Low */
#define UART_IER_OFFSET		(UART_BASE + (1 << REG_SHIFT))	/* I/O: Interrupt Enable Register */
#define UART_DLM_OFFSET		(UART_BASE + (1 << REG_SHIFT))	/* Out: Divisor Latch High */
#define UART_FCR_OFFSET		(UART_BASE + (2 << REG_SHIFT))	/* Out: FIFO Control Register */
#define UART_IIR_OFFSET		(UART_BASE + (2 << REG_SHIFT))	/* I/O: Interrupt Identification Register */
#define UART_LCR_OFFSET		(UART_BASE + (3 << REG_SHIFT))	/* Out: Line Control Register */
#define UART_MCR_OFFSET		(UART_BASE + (4 << REG_SHIFT))	/* Out: Modem Control Register */
#define UART_LSR_OFFSET		(UART_BASE + (5 << REG_SHIFT))	/* In:  Line Status Register */
#define UART_MSR_OFFSET		(UART_BASE + (6 << REG_SHIFT))	/* In:  Modem Status Register */
#define UART_SCR_OFFSET		(UART_BASE + (7 << REG_SHIFT))	/* I/O: Scratch Register */
#define UART_MDR1_OFFSET	(UART_BASE + (8 << REG_SHIFT))	/* I/O:  Mode Register */

#define UART_LSR_FIFOE		0x80	/* Fifo error */
#define UART_LSR_TEMT		0x40	/* Transmitter empty */
#define UART_LSR_THRE		0x20	/* Transmit-hold-register empty */
#define UART_LSR_BI		0x10	/* Break interrupt indicator */
#define UART_LSR_FE		0x08	/* Frame error indicator */
#define UART_LSR_PE		0x04	/* Parity error indicator */
#define UART_LSR_OE		0x02	/* Overrun error indicator */
#define UART_LSR_DR		0x01	/* Receiver data ready */
#define UART_LSR_BRK_ERROR_BITS	0x1E	/* BI, FE, PE, OE bits */

void uart_init(void);
void uart_putc(char c);
void uart_puts(char* str);

void print_hart_info(unsigned int hart);
void print_downloading_info(unsigned int from, unsigned int to, unsigned int size);

#endif  /*_UART_H */
