#include <uart.h>
#include <asm/mmio.h>

#define DDR_DST  0x8c800000
#define DDR_BASE  0x80000000
extern const unsigned char _boot2bin_start[];
extern const unsigned char _boot2bin_end[];
#define CLINT_BASE 0x38000000
#define CLINT_SIP_BASE  0x0

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

void gpio(void)
{
        
        register int i asm("t0") = 0;
        i = readl(0x40050);	
        i = readl(0x40054);	
        i = readl(0x40058);	
        i = readl(0x4005c);	
	writel(0xd0108,0x1f);
	writel(0xd0114,0x1f);

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
void boot_core1(void)
{
	((void (*) ())DDR_BASE)();
	while(1){};
}
void _main(void)
{
        flash_cpy((void*)_boot2bin_start, (void*)DDR_DST, ((long)_boot2bin_end - (long)_boot2bin_start)/8);
	asm volatile("fence");
	((void (*) ())DDR_DST)();
	while(1){};
}
