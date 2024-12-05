#include <asm/mmio.h>
#include <pll.h>

#define CRU_BASE 0xd0000
#define PLL_CTRL4_BASE  (CRU_BASE + 0x80)

void pll_core(void)
{
	//core_pll
	writel(0xd0040,0x1307d);
	writel(0xd0044,0x0);
	writel(0xd0048,0x300);
	writel(0xd004c,0x80);
}

void pll_address(void)
{
	writel(PLL_CTRL4_BASE + 0x0, 0x1207d);
	writel(PLL_CTRL4_BASE + 0x4, 0x0);
	writel(PLL_CTRL4_BASE + 0x8, 0x300);
	writel(PLL_CTRL4_BASE + 0xc, 0x88);
}

void pll_enable(void)
{
	writel(0xd0008,0x22);
}
