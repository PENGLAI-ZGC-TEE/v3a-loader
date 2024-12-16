#include <uart.h>
#include <asm/mmio.h>

#define DDR_BASE  0x80000000
#define FLASH_SRC 0x4200000 
#define DDR_DST   0x80000000
#define BIN_SIZE  0x1f00000

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

void _main(void)
{
	writel(0xb0014, 0x15501003);
        flash_cpy((void*)FLASH_SRC, (void*)DDR_DST, BIN_SIZE/8);
	writel(UART_BASE + 0, 'J');
	writel(0x38000004, 1);
	asm volatile("fence.i");
	((void (*) ())DDR_BASE)();
	while(1){};
}
