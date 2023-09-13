#include "uart.h"
#include <asm/type.h>

typedef __builtin_va_list __gnuc_va_list;
typedef __gnuc_va_list va_list;

const unsigned char hex_tab[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};

#define  MAX_NUMBER_BYTES  64
#define va_start(v,l) __builtin_va_start(v,l)
#define va_end(v) __builtin_va_end(v)
#define va_arg(v,l) __builtin_va_arg(v,l)

static void out_num(long n, int base, char lead, int maxwidth)
{
	unsigned long m = 0;
	char buf[MAX_NUMBER_BYTES], *s = buf + sizeof(buf);
	int count = 0, i = 0;

	*--s = '\0';

	if (n < 0)
		m = -n;
	else
		m = n;

	do
	{
		*--s = hex_tab[m % base];
		count++;

		if(base == 2 && (count % 8 == 0)) {*--s = ' ';}
	}
	while ((m /= base) != 0);

	if( maxwidth && count < maxwidth)
	{
		for (i = maxwidth - count; i; i--)
		{
			*--s = lead;
			if(base == 2 && ( (++count) %8 == 0)) {*--s = ' ';}
		}
	}

	if (n < 0)
		*--s = '-';

	uart_puts(s);
}

static int my_vprintf(const char *fmt, va_list ap)
{
	char lead = ' ';
	int  maxwidth = 0;

	for(; *fmt != '\0'; fmt++)
	{
		if (*fmt != '%')
		{
			uart_putc(*fmt);
			continue;
		}
		lead = ' ';
		maxwidth = 0;

		fmt++;
		if(*fmt == '0')
		{
			lead = '0';
			fmt++;
		}

		while(*fmt >= '0' && *fmt <= '9')
		{
			maxwidth *= 10;
			maxwidth += (*fmt - '0');
			fmt++;
		}

		switch (*fmt)
		{
			case 'd':
				out_num(va_arg(ap, s64), 10, lead, maxwidth);
				break;
			case 'o':
				out_num(va_arg(ap, u64),  8, lead, maxwidth);
				break;
			case 'u':
				out_num(va_arg(ap, u64), 10, lead, maxwidth);
				break;
			case 'x':
			case 'X':
				out_num(va_arg(ap, u64), 16, lead, maxwidth);
				break;
			case 'b':
				out_num(va_arg(ap, u64),  2, lead, maxwidth);
				break;
			case 'c':
				uart_putc(va_arg(ap, int));
				break;
			case 's':
				uart_puts(va_arg(ap, char *));
				break;

			default:
				uart_putc(*fmt);
				break;
		}
	}
	
	return 0;
}

int print(const char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	my_vprintf(fmt, ap);
	va_end(ap);

	return 0;
}

void print_hart_info(unsigned int hart_id)
{
	print("hart id: %d\r\n", hart_id);
}

void print_downloading_info(unsigned int from, 
			    unsigned int to, 
			    unsigned int size)
{
	print("downloading... please wait...\r\n");
	print("src: 0x%x\r\n", from);
	print("dst: 0x%x\r\n", to);
	print("size: %d\r\n", size);
}
