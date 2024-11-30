#include <uart.h>
#include <asm/mmio.h>

#define DDR_BASE  0x80000000
#define FLASH_SRC 0x2500000 
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

void soc_cru(void)
{
	writel(0xd0104, 0xc000);
	writel(0xd0108, 0x003f);
	writel(0xd0110, 0xc000);
	writel(0xd0114, 0x003f);
}
void gpio(void)
{
        
        register int i asm("t0") = 0;
        i = readl(0x40050);	
        i = readl(0x40054);	
        i = readl(0x40058);	
        i = readl(0x4005c);	
//	writel(0xd0100, 0xffffff00);
//	writel(0xd0104, 0xffffffff);

	writel(0x40004, 0xffffffff);
	writel(0x40010, 0xffffffff);
	writel(0x4001c, 0xffffffff);
	writel(0x40028, 0xffffffff);

        i = 0; 
	while(1){
		writel(0x40000, 0xffffffff);
		writel(0x4000c, 0xffffffff);
		writel(0x40018, 0xffffffff);
		writel(0x40024, 0xffffffff);
		for(i = 0; i < 0x1000; i++){}
		writel(0x40000, 0x0);
		writel(0x4000c, 0x0);
		writel(0x40018, 0x0);
		writel(0x40024, 0x0);
		for(i = 0; i < 0x1000; i++){}
	}
}
void _main(void)
{
        flash_cpy((void*)FLASH_SRC, (void*)DDR_DST, BIN_SIZE/8);
	writel(UART_BASE + 0, 'L');
	((void (*) ())DDR_BASE)();
	while(1){};
}
