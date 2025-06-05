#include <uart.h>
#include <asm/mmio.h>
#include <print.h>
#include <pll.h>
#include <qspi.h>

#define DDR_BASE  0x80000000
#define FLASH_SRC 0x4200000
#define DDR_DST   0x80000000
#define PAY_START 0x8cb00000
#define PAY_END   0x8cb00008

#define MACRO(j) ramStart[i + j] = romStart[i + j]
#define MACRO4(j) MACRO(j); MACRO(j + 1); MACRO(j + 2); MACRO(j + 3);
typedef unsigned long long   uint64_t;

void flash_cpy(void* src, void* dst, uint64_t size)
{
	uint64_t *romStart = (uint64_t *)(unsigned long long)src;
	uint64_t *ramStart = (uint64_t *)(unsigned long long)dst;

	uint64_t i = 0;
	for (i = 0; i < size; i += 16) {
		MACRO4(0); MACRO4(4); MACRO4(8); MACRO4(12);
	}
}

void boot2_core1(void)
{
	((void (*) ())DDR_BASE)();
	while(1){};
}
void _main(void)
{
	unsigned long pay_start = *((volatile unsigned long *)(PAY_START));
	qspi_init();
	asm volatile("fence.i");
	qspi_nonv_cfg(0xa8f6);
	asm volatile("fence.i");
        flash_cpy((void*)pay_start, (void*)DDR_DST, (*((volatile unsigned long *)(PAY_END)) - *((volatile unsigned long *)(PAY_START)))/8 + 1);
        my_print("\r\n");
#ifdef CORE_1_G
        my_print("core frq 1G \r\n");
#endif
#ifdef CORE_1_5G
        my_print("core frq 1.5G \r\n");
#endif
#ifdef DDR_1600
        my_print("ddr frq 1600 \r\n");
#endif
#ifdef DDR_2100
        my_print("ddr frq 2132 \r\n");
#endif
#ifdef DDR_2400
        my_print("ddr frq 2400 \r\n");
#endif

	qspi_nonv_cfg(0xa8f7);
	qspi_enter_xip();
	asm volatile("fence.i");
	writel(0x38000004, 1);
	((void (*) ())DDR_BASE)();
	while(1){};
}
