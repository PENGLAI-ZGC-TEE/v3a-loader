#include <asm/mmio.h>
#include "uart.h"
#define CPU_PLL_CTL1_BASE  0xd0050
#define CRU_BASE   0xd0000
void init_ddr(void)
{
#ifndef FAKE_DDR
    register int rd_data asm ("t0");
//  unsigned int rd_data_temp=0;
//register unsigned long *debug_val asm("t2")= 0;
    //*debug_val = 0;
    //mc config
    writel(UART_BASE + 0, 'A');
    writel(0x00130304, 0x00000001);
                                      //writel(0x00130030, 0x00000001); 
    writel(0x00130000, 0x40040410);
    writel(0x00130010, 0x00000010);
    writel(0x00130014, 0x00000000);//writel(0x00130014, 0x0000465c);
    writel(0x0013001c, 0x00000000);//writel(0x0013001c, 0xa2e0f445);
    writel(0x00130030, 0x00000080);//writel(0x00130030, 0x00000088);
                                      //writel(0x00130034, 0x000f0002);
    writel(0x00130038, 0x006a0000);
    writel(0x00130050, 0x00001070);//writel(0x00130050, 0x00001060);
    writel(0x00130060, 0x00000000);
    writel(0x00130064, 0x0061008c);//writel(0x00130064, 0x009200d3);
    writel(0x001300c0, 0x00000000);
    writel(0x001300c4, 0x00001000);//writel(0x001300c4, 0x00001010);
    writel(0x001300d0, 0x00020125);//writel(0x001300d0, 0x00020027);
    writel(0x001300d4, 0x00760000);//writel(0x001300d4, 0x00270006);
    writel(0x001300dc, 0x02050001);//writel(0x001300dc, 0x0a310001);
    writel(0x001300e0, 0x00000000);//writel(0x001300e0, 0x10180200);
    writel(0x001300e4, 0x00100000);//writel(0x001300e4, 0x00110000);
    writel(0x001300e8, 0x00000440);//writel(0x001300e8, 0x00000640);
    writel(0x001300ec, 0x00000400);//writel(0x001300ec, 0x00000800);
    writel(0x001300f0, 0x00000010);
    writel(0x00130100, 0x0D0A1A0E);//writel(0x00130100, 0x110d2914);
    writel(0x00130104, 0x00030313);//writel(0x00130104, 0x0004051b);
    writel(0x00130108, 0x0505040A);//writel(0x00130108, 0x06080510);
    writel(0x0013010c, 0x0000400C);//writel(0x0013010c, 0x0000f00f);
    writel(0x00130110, 0x05030306);//writel(0x00130110, 0x08030309);
    writel(0x00130114, 0x04040302);//writel(0x00130114, 0x0f0e0404);
    writel(0x00130120, 0x04040A07);//writel(0x00130120, 0x06060e08);
    writel(0x00130124, 0x00020208);//writel(0x00130124, 0x0002020d);
    writel(0x00130128, 0x000E0C05);//writel(0x00130128, 0x000f0e05);
    writel(0x0013012c, 0x1107010E);//writel(0x0013012c, 0x14090112);
    writel(0x00130130, 0x0C000008);//writel(0x00130130, 0x0c00000d);
    writel(0x0013013c, 0x00000000);
    writel(0x00130180, 0x51000040);
    writel(0x00130184, 0x00000070);
    writel(0x00130190, 0x04868207);//writel(0x00130190, 0x048b820a);
    writel(0x00130194, 0x01090606);
    writel(0x00130198, 0x07008120);
    writel(0x0013019c, 0x00000061);
    writel(0x001301a0, 0x20400004);
    writel(0x001301a4, 0x0003002e);
    writel(0x001301a8, 0x00000000);
    writel(0x001301b0, 0x00000041);
    writel(0x001301b8, 0x00000000);
    writel(0x001301c0, 0x00000001);
    writel(0x001301c4, 0x00000000);
    writel(0x00130204, 0x003f0c0c);//writel(0x00130204, 0x003f0007);
    writel(0x00130208, 0x01010100);//writel(0x00130208, 0x03000400);
    writel(0x0013020c, 0x01010101);//writel(0x0013020c, 0x02020507);
    writel(0x00130210, 0x00001f1f);
    writel(0x00130214, 0x08080505);//writel(0x00130214, 0x0b080709);
    writel(0x00130218, 0x08080808);//writel(0x00130218, 0x0406080b);
    writel(0x0013021c, 0x00000f0f);
    writel(0x00130220, 0x00000a01);//writel(0x00130220, 0x00000204);
    writel(0x00130224, 0x02020107);
    writel(0x00130228, 0x0704080a);
    writel(0x0013022c, 0x00000007);
    writel(0x00130240, 0x0608061C);//writel(0x00130240, 0x0f1e0264);
    writel(0x00130244, 0x00000010);//writel(0x00130244, 0x00000001);
    writel(0x00130250, 0x1aa51704);
    writel(0x00130254, 0x00000039);
    writel(0x0013025c, 0x40001e0b);
    writel(0x00130264, 0x2c006921);
    writel(0x0013026c, 0x79001d5c);
    writel(0x00130300, 0x00000001);
    writel(0x00130304, 0x00000000);
    writel(0x0013030c, 0x00000000);
    writel(0x00130320, 0x00000001);
    writel(0x00130328, 0x00000000);
    writel(0x0013036c, 0x00000010);
    writel(0x00130400, 0x00000010);
    writel(0x00130404, 0x000023e7);
    writel(0x00130408, 0x0000036e);
    writel(0x00130490, 0x00000000);
    writel(0x00130494, 0x00010005);
    writel(UART_BASE + 0, 'B');
    // mc reset done
    rd_data = readl(0x00130ff4);
    writel(CPU_PLL_CTL1_BASE + 0x0, 0x13064);//pll1foutpostdiv=(24*200/3/3/1)=533.3MHz
    writel(CPU_PLL_CTL1_BASE + 0x4, 0x0    );
    writel(CPU_PLL_CTL1_BASE + 0x8, 0x200  );
    writel(CPU_PLL_CTL1_BASE + 0xc, 0x80   );
	writel(CRU_BASE + 0x8, 0x26);
    // mc init
    writel(0x00130304, 0x00000000);
    writel(0x00130030, 0x00000088);
    writel(0x00130030, 0x00000088);
    writel(0x00130320, 0x00000000);
    writel(0x001301b0, 0x00000040);
    // phy config
    writel(0x00140090, 0x0020403b);
    writel(0x00140520, 0x0f000009);
    writel(0x00140524, 0x00000309);
    writel(0x00140710, 0x0e00003c);
    writel(0x00140810, 0x0e00003c);
    writel(0x00140910, 0x0e00003c);
    writel(0x00140A10, 0x0e00003c);
    writel(0x00140B10, 0x0e00003c);
    writel(0x00140C10, 0x0e00003c);
    writel(0x00140D10, 0x0e00003c);
    writel(0x00140E10, 0x0e00003c);
    writel(0x00140200, 0x8000b0cf);//writel(0x00140200, 0x3000b0c7);
    writel(0x0014052C, 0x0fc00172);
    writel(0x00140100, 0x2800040c);
    writel(0x00140088, 0x20c01004);//writel(0x00140088, 0x20c01884);
    writel(0x00140040, 0x5e001810);
    writel(0x00140044, 0x008005f0);
    writel(0x00140180, 0x00000205);//writel(0x00140180, 0x00000a31);
    writel(0x00140184, 0x00000001);
    writel(0x00140188, 0x00000000);//writel(0x00140188, 0x00000018);
    writel(0x0014018C, 0x00000000);//writel(0x0014018C, 0x00000200);
    writel(0x00140190, 0x00000000);
    writel(0x00140194, 0x00000440);//writel(0x00140194, 0x00000640);
    writel(0x00140198, 0x00000400);//writel(0x00140200, 0x3000b0c7);
									  //writel(0x00140198, 0x00000800);
    writel(0x00140110, 0x051C0A06);//writel(0x00140110, 0x0627100a);
    writel(0x00140114, 0x28141808);//writel(0x00140114, 0x281a0408);
    writel(0x00140118, 0x000401B0);//writel(0x00140118, 0x00070380);
    writel(0x0014011C, 0x02550101);//writel(0x0014011C, 0x02000101);
    writel(0x00140120, 0x01A40605);//writel(0x00140120, 0x01cd0608);
    writel(0x00140124, 0x00260A06);//writel(0x00140124, 0x0036100a);
    writel(0x00140014, 0x020046a0);
    writel(0x00140018, 0x20006c2b);
    writel(0x0014001C, 0xc0aa0060);
    writel(0x0014002C, 0x80040000);
    writel(0x00140004, 0x00000073);
	//phy init
	rd_data = 0x0;
    while (rd_data != 0x8000000f ){ 
    rd_data = readl(0x00140034);
    }
	//phy SDRAM config
    writel(0x00140004, 0x00040001);
	//phy SDRAM init
    //while(1){};
	rd_data = 0x0;
    while (rd_data != 0x8000001f ){ 
    rd_data = readl(0x00140034);
    }
	//mc SDRAM config
    writel(0x001301b0, 0x00000041);
    writel(0x00130320, 0x00000001);
	//mc SDRAM init
	rd_data = 0x0;
    while ((rd_data&0x1) == 0 ){ 
    rd_data = readl(0x00130004);
    }
    writel(UART_BASE + 0, 'C');
    // mc SDRAM config reset
    writel(0x00130320, 0x00000000);
    writel(0x00130060, 0x00000001);
    writel(0x001301b0, 0x00000040);
    writel(0x00130320, 0x00000001);
    writel(0x00130010, 0x00001010);
    writel(0x00130014, 0x00000181);
    writel(0x00130010, 0x80001010);
    // write leveling config
    writel(0x00140314, 0x000000ff);
    writel(0x001404DC, 0x00000000);
    writel(0x00140098, 0x00010000);
    writel(0x00140004, 0x00000201);
	
    // write leveling training
	rd_data = 0x0;
    while (rd_data != 0x8000003f ){ 
    rd_data = readl(0x00140034);
//	rd_data = readl(0x001407d0);
//	rd_data = readl(0x001407d4);
//	rd_data = readl(0x001407d8);
//	rd_data = readl(0x001407dc);
	}
    // write leveling config reset
    writel(0x001404DC, 0x00000000);//add
	writel(0x00140098, 0x00000001);//add
    writel(0x00130010, 0x00001010);
    writel(0x00130014, 0x00000101);
    writel(0x00130010, 0x80001010);
    // read & write training config
    writel(0x00140004, 0x0002fc01);
	// read & write training
	rd_data = 0x0;
    while (rd_data != 0x80004fff ){ 
    rd_data = readl(0x00140034);
    }
    writel(UART_BASE + 0, 'D');
    // mc final config
    writel(0x00130320, 0x00000000);
    writel(0x00130060, 0x00000000);
    writel(0x00130320, 0x00000001);
    writel(0x00130490, 0x00000001);
    writel(UART_BASE + 0, 'E');
#endif
}
