#include <asm/mmio.h>

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
    /*REG_WRITE(0x00130304, 0x00000001);*/asm volatile("li t0, 0x00000001\n\t" "li t1, 0x00130304\n\t" "sw t0, 0x0(t1)\n\t" /*"lw t2, 0x0(t1) \n\t" "li t3, 0x1\n\t" "beq t0, t2, 1f\n\t" "addi t3, t3, 0x1\n\t" "1: nop"*/);
    /*REG_WRITE(0x00130030, 0x00000001);*/asm volatile("li t0, 0x00000001\n\t" "li t1, 0x00130030\n\t" "sw t0, 0x0(t1)\n\t" ); 
    /*REG_WRITE(0x00130000, 0x40040610);*/asm volatile("li t0, 0x40040610\n\t" "li t1, 0x00130000\n\t" "sw t0, 0x0(t1)\n\t" );
    /*REG_WRITE(0x00130010, 0x00000010);*/asm volatile("li t0, 0x00000010\n\t" "li t1, 0x00130010\n\t" "sw t0, 0x0(t1)\n\t" );
    /*REG_WRITE(0x00130014, 0x0000465c);*/asm volatile("li t0, 0x0000465c\n\t" "li t1, 0x00130014\n\t" "sw t0, 0x0(t1)\n\t" );
    /*REG_WRITE(0x0013001c, 0xa2e0f445);*/asm volatile("li t0, 0xa2e0f445\n\t" "li t1, 0x0013001c\n\t" "sw t0, 0x0(t1)\n\t" );
    /*REG_WRITE(0x00130030, 0x00000088);*/asm volatile("li t0, 0x00000088\n\t" "li t1, 0x00130030\n\t" "sw t0, 0x0(t1)\n\t" );
    /*REG_WRITE(0x00130034, 0x000f0002);*/asm volatile("li t0, 0x000f0002\n\t" "li t1, 0x00130034\n\t" "sw t0, 0x0(t1)\n\t" );
    /*REG_WRITE(0x00130038, 0x006a0000);*/asm volatile("li t0, 0x006a0000\n\t" "li t1, 0x00130038\n\t" "sw t0, 0x0(t1)\n\t" );
    /*REG_WRITE(0x00130050, 0x00001060);*/asm volatile("li t0, 0x00001060\n\t" "li t1, 0x00130050\n\t" "sw t0, 0x0(t1)\n\t" );
    /*REG_WRITE(0x00130060, 0x00000000);*/asm volatile("li t0, 0x00000000\n\t" "li t1, 0x00130060\n\t" "sw t0, 0x0(t1)\n\t" );
    /*REG_WRITE(0x00130064, 0x009200d3);*/asm volatile("li t0, 0x009200d3\n\t" "li t1, 0x00130064\n\t" "sw t0, 0x0(t1)\n\t" );
    /*REG_WRITE(0x001300c0, 0x00000000);*/asm volatile("li t0, 0x00000000\n\t" "li t1, 0x001300c0\n\t" "sw t0, 0x0(t1)\n\t" );
    /*REG_WRITE(0x001300c4, 0x00001010);*/asm volatile("li t0, 0x00001010\n\t" "li t1, 0x001300c4\n\t" "sw t0, 0x0(t1)\n\t" );
    /*REG_WRITE(0x001300d0, 0x00020027);*/asm volatile("li t0, 0x00020027\n\t" "li t1, 0x001300d0\n\t" "sw t0, 0x0(t1)\n\t" );
    /*REG_WRITE(0x001300d4, 0x00270006);*/asm volatile("li t0, 0x00270006\n\t" "li t1, 0x001300d4\n\t" "sw t0, 0x0(t1)\n\t" );
    /*REG_WRITE(0x001300dc, 0x0a310001);*/asm volatile("li t0, 0x0a310001\n\t" "li t1, 0x001300dc\n\t" "sw t0, 0x0(t1)\n\t" );
    /*REG_WRITE(0x001300e0, 0x10180200);*/asm volatile("li t0, 0x10180200\n\t" "li t1, 0x001300e0\n\t" "sw t0, 0x0(t1)\n\t" );
    /*REG_WRITE(0x001300e4, 0x00110000);*/asm volatile("li t0, 0x00110000\n\t" "li t1, 0x001300e4\n\t" "sw t0, 0x0(t1)\n\t" );
    /*REG_WRITE(0x001300e8, 0x00000640);*/asm volatile("li t0, 0x00000640\n\t" "li t1, 0x001300e8\n\t" "sw t0, 0x0(t1)\n\t" );
    /*REG_WRITE(0x001300ec, 0x00000800);*/asm volatile("li t0, 0x00000800\n\t" "li t1, 0x001300ec\n\t" "sw t0, 0x0(t1)\n\t" );
    /*REG_WRITE(0x001300f0, 0x00000010);*/asm volatile("li t0, 0x00000010\n\t" "li t1, 0x001300f0\n\t" "sw t0, 0x0(t1)\n\t" );
    /*REG_WRITE(0x00130100, 0x110d2914);*/asm volatile("li t0, 0x110d2914\n\t" "li t1, 0x00130100\n\t" "sw t0, 0x0(t1)\n\t" );
    /*REG_WRITE(0x00130104, 0x0004051b);*/asm volatile("li t0, 0x0004051b\n\t" "li t1, 0x00130104\n\t" "sw t0, 0x0(t1)\n\t" );
    /*REG_WRITE(0x00130108, 0x06080510);*/asm volatile("li t0, 0x06080510\n\t" "li t1, 0x00130108\n\t" "sw t0, 0x0(t1)\n\t" );
    /*REG_WRITE(0x0013010c, 0x0000f00f);*/asm volatile("li t0, 0x0000f00f\n\t" "li t1, 0x0013010c\n\t" "sw t0, 0x0(t1)\n\t" );
    /*REG_WRITE(0x00130110, 0x08030309);*/asm volatile("li t0, 0x08030309\n\t" "li t1, 0x00130110\n\t" "sw t0, 0x0(t1)\n\t" );
    /*REG_WRITE(0x00130114, 0x0f0e0404);*/asm volatile("li t0, 0x0f0e0404\n\t" "li t1, 0x00130114\n\t" "sw t0, 0x0(t1)\n\t" );
    /*REG_WRITE(0x00130120, 0x06060e08);*/asm volatile("li t0, 0x06060e08\n\t" "li t1, 0x00130120\n\t" "sw t0, 0x0(t1)\n\t" );
    /*REG_WRITE(0x00130124, 0x0002020d);*/asm volatile("li t0, 0x0002020d\n\t" "li t1, 0x00130124\n\t" "sw t0, 0x0(t1)\n\t" );
    /*REG_WRITE(0x00130128, 0x000f0e05);*/asm volatile("li t0, 0x000f0e05\n\t" "li t1, 0x00130128\n\t" "sw t0, 0x0(t1)\n\t" );
    /*REG_WRITE(0x0013012c, 0x14090112);*/asm volatile("li t0, 0x14090112\n\t" "li t1, 0x0013012c\n\t" "sw t0, 0x0(t1)\n\t" );
    /*REG_WRITE(0x00130130, 0x0c00000d);*/asm volatile("li t0, 0x0c00000d\n\t" "li t1, 0x00130130\n\t" "sw t0, 0x0(t1)\n\t" );
    /*REG_WRITE(0x0013013c, 0x00000000);*/asm volatile("li t0, 0x00000000\n\t" "li t1, 0x0013013c\n\t" "sw t0, 0x0(t1)\n\t" );
    /*REG_WRITE(0x00130180, 0x51000040);*/asm volatile("li t0, 0x51000040\n\t" "li t1, 0x00130180\n\t" "sw t0, 0x0(t1)\n\t" );
    /*REG_WRITE(0x00130184, 0x00000070);*/asm volatile("li t0, 0x00000070\n\t" "li t1, 0x00130184\n\t" "sw t0, 0x0(t1)\n\t" );
    /*REG_WRITE(0x00130190, 0x048b820a);*/asm volatile("li t0, 0x048b820a\n\t" "li t1, 0x00130190\n\t" "sw t0, 0x0(t1)\n\t" );
    /*REG_WRITE(0x00130194, 0x01090606);*/asm volatile("li t0, 0x01090606\n\t" "li t1, 0x00130194\n\t" "sw t0, 0x0(t1)\n\t" );
    /*REG_WRITE(0x00130198, 0x07008120);*/asm volatile("li t0, 0x07008120\n\t" "li t1, 0x00130198\n\t" "sw t0, 0x0(t1)\n\t" );
    /*REG_WRITE(0x0013019c, 0x00000061);*/asm volatile("li t0, 0x00000061\n\t" "li t1, 0x0013019c\n\t" "sw t0, 0x0(t1)\n\t" );
    /*REG_WRITE(0x001301a0, 0x20400004);*/asm volatile("li t0, 0x20400004\n\t" "li t1, 0x001301a0\n\t" "sw t0, 0x0(t1)\n\t" );
    /*REG_WRITE(0x001301a4, 0x0003002e);*/asm volatile("li t0, 0x0003002e\n\t" "li t1, 0x001301a4\n\t" "sw t0, 0x0(t1)\n\t" );
    /*REG_WRITE(0x001301a8, 0x00000000);*/asm volatile("li t0, 0x00000000\n\t" "li t1, 0x001301a8\n\t" "sw t0, 0x0(t1)\n\t" );
    /*REG_WRITE(0x001301b0, 0x00000041);*/asm volatile("li t0, 0x00000041\n\t" "li t1, 0x001301b0\n\t" "sw t0, 0x0(t1)\n\t" );
    /*REG_WRITE(0x001301b8, 0x00000000);*/asm volatile("li t0, 0x00000000\n\t" "li t1, 0x001301b8\n\t" "sw t0, 0x0(t1)\n\t" );
    /*REG_WRITE(0x001301c0, 0x00000001);*/asm volatile("li t0, 0x00000001\n\t" "li t1, 0x001301c0\n\t" "sw t0, 0x0(t1)\n\t" );
    /*REG_WRITE(0x001301c4, 0x00000000);*/asm volatile("li t0, 0x00000000\n\t" "li t1, 0x001301c4\n\t" "sw t0, 0x0(t1)\n\t" );
    /*REG_WRITE(0x00130204, 0x003f0007);*/asm volatile("li t0, 0x003f0007\n\t" "li t1, 0x00130204\n\t" "sw t0, 0x0(t1)\n\t" );
    /*REG_WRITE(0x00130208, 0x03000400);*/asm volatile("li t0, 0x03000400\n\t" "li t1, 0x00130208\n\t" "sw t0, 0x0(t1)\n\t" );
    /*REG_WRITE(0x0013020c, 0x02020507);*/asm volatile("li t0, 0x02020507\n\t" "li t1, 0x0013020c\n\t" "sw t0, 0x0(t1)\n\t" );
    /*REG_WRITE(0x00130210, 0x00001f1f);*/asm volatile("li t0, 0x00001f1f\n\t" "li t1, 0x00130210\n\t" "sw t0, 0x0(t1)\n\t" );
    /*REG_WRITE(0x00130214, 0x0b080709);*/asm volatile("li t0, 0x0b080709\n\t" "li t1, 0x00130214\n\t" "sw t0, 0x0(t1)\n\t" );
    /*REG_WRITE(0x00130218, 0x0406080b);*/asm volatile("li t0, 0x0406080b\n\t" "li t1, 0x00130218\n\t" "sw t0, 0x0(t1)\n\t" );
    /*REG_WRITE(0x0013021c, 0x00000f0f);*/asm volatile("li t0, 0x00000f0f\n\t" "li t1, 0x0013021c\n\t" "sw t0, 0x0(t1)\n\t" );
    /*REG_WRITE(0x00130220, 0x00000204);*/asm volatile("li t0, 0x00000204\n\t" "li t1, 0x00130220\n\t" "sw t0, 0x0(t1)\n\t" );
    /*REG_WRITE(0x00130224, 0x02020107);*/asm volatile("li t0, 0x02020107\n\t" "li t1, 0x00130224\n\t" "sw t0, 0x0(t1)\n\t" );
    /*REG_WRITE(0x00130228, 0x0704080a);*/asm volatile("li t0, 0x0704080a\n\t" "li t1, 0x00130228\n\t" "sw t0, 0x0(t1)\n\t" );
    /*REG_WRITE(0x0013022c, 0x00000007);*/asm volatile("li t0, 0x00000007\n\t" "li t1, 0x0013022c\n\t" "sw t0, 0x0(t1)\n\t" );
    /*REG_WRITE(0x00130240, 0x0f1e0264);*/asm volatile("li t0, 0x0f1e0264\n\t" "li t1, 0x00130240\n\t" "sw t0, 0x0(t1)\n\t" );
    /*REG_WRITE(0x00130244, 0x00000001);*/asm volatile("li t0, 0x00000001\n\t" "li t1, 0x00130244\n\t" "sw t0, 0x0(t1)\n\t" );
    /*REG_WRITE(0x00130250, 0x1aa51704);*/asm volatile("li t0, 0x1aa51704\n\t" "li t1, 0x00130250\n\t" "sw t0, 0x0(t1)\n\t" );
    /*REG_WRITE(0x00130254, 0x00000039);*/asm volatile("li t0, 0x00000039\n\t" "li t1, 0x00130254\n\t" "sw t0, 0x0(t1)\n\t" );
    /*REG_WRITE(0x0013025c, 0x40001e0b);*/asm volatile("li t0, 0x40001e0b\n\t" "li t1, 0x0013025c\n\t" "sw t0, 0x0(t1)\n\t" );
    /*REG_WRITE(0x00130264, 0x2c006921);*/asm volatile("li t0, 0x2c006921\n\t" "li t1, 0x00130264\n\t" "sw t0, 0x0(t1)\n\t" );
    /*REG_WRITE(0x0013026c, 0x79001d5c);*/asm volatile("li t0, 0x79001d5c\n\t" "li t1, 0x0013026c\n\t" "sw t0, 0x0(t1)\n\t" );
    /*REG_WRITE(0x00130300, 0x00000001);*/asm volatile("li t0, 0x00000001\n\t" "li t1, 0x00130300\n\t" "sw t0, 0x0(t1)\n\t" );
    /*REG_WRITE(0x00130304, 0x00000000);*/asm volatile("li t0, 0x00000000\n\t" "li t1, 0x00130304\n\t" "sw t0, 0x0(t1)\n\t" );
    /*REG_WRITE(0x0013030c, 0x00000000);*/asm volatile("li t0, 0x00000000\n\t" "li t1, 0x0013030c\n\t" "sw t0, 0x0(t1)\n\t" );
    /*REG_WRITE(0x00130320, 0x00000001);*/asm volatile("li t0, 0x00000001\n\t" "li t1, 0x00130320\n\t" "sw t0, 0x0(t1)\n\t" );
    /*REG_WRITE(0x00130328, 0x00000000);*/asm volatile("li t0, 0x00000000\n\t" "li t1, 0x00130328\n\t" "sw t0, 0x0(t1)\n\t" );
    /*REG_WRITE(0x0013036c, 0x00000010);*/asm volatile("li t0, 0x00000010\n\t" "li t1, 0x0013036c\n\t" "sw t0, 0x0(t1)\n\t" );
    /*REG_WRITE(0x00130400, 0x00000010);*/asm volatile("li t0, 0x00000010\n\t" "li t1, 0x00130400\n\t" "sw t0, 0x0(t1)\n\t" );
    /*REG_WRITE(0x00130404, 0x000023e7);*/asm volatile("li t0, 0x000023e7\n\t" "li t1, 0x00130404\n\t" "sw t0, 0x0(t1)\n\t" );
    /*REG_WRITE(0x00130408, 0x0000036e);*/asm volatile("li t0, 0x0000036e\n\t" "li t1, 0x00130408\n\t" "sw t0, 0x0(t1)\n\t" );
    /*REG_WRITE(0x00130490, 0x00000000);*/asm volatile("li t0, 0x00000000\n\t" "li t1, 0x00130490\n\t" "sw t0, 0x0(t1)\n\t" );
    /*REG_WRITE(0x00130494, 0x00010005);*/asm volatile("li t0, 0x00010005\n\t" "li t1, 0x00130494\n\t" "sw t0, 0x0(t1)\n\t" );
    // mc reset done
    rd_data = readl(0x00130ff4);
    writel(CPU_PLL_CTL1_BASE + 0x0, 0x13096);//pll1foutpostdiv=(24*200/3/3/1)=533.3MHz
    writel(CPU_PLL_CTL1_BASE + 0x4, 0x0    );
    writel(CPU_PLL_CTL1_BASE + 0x8, 0x200  );
    writel(CPU_PLL_CTL1_BASE + 0xc, 0x80   );
    writel(CRU_BASE + 0x8, 0x26);
    // mc init
    /*REG_WRITE(0x00130304, 0x00000000);*/asm volatile("li t0, 0x00000000\n\t" "li t1, 0x00130304\n\t" "sw t0, 0x0(t1)\n\t" );
    /*REG_WRITE(0x00130030, 0x00000088);*/asm volatile("li t0, 0x00000088\n\t" "li t1, 0x00130030\n\t" "sw t0, 0x0(t1)\n\t" );
    /*REG_WRITE(0x00130030, 0x00000088);*/asm volatile("li t0, 0x00000088\n\t" "li t1, 0x00130030\n\t" "sw t0, 0x0(t1)\n\t" );
    /*REG_WRITE(0x00130320, 0x00000000);*/asm volatile("li t0, 0x00000000\n\t" "li t1, 0x00130320\n\t" "sw t0, 0x0(t1)\n\t" );
    /*REG_WRITE(0x001301b0, 0x00000040);*/asm volatile("li t0, 0x00000040\n\t" "li t1, 0x001301b0\n\t" "sw t0, 0x0(t1)\n\t" );
    // phy config
    /*REG_WRITE(0x00140090, 0x0020403b);*/asm volatile("li t0, 0x0020403b\n\t" "li t1, 0x00140090\n\t" "sw t0, 0x0(t1)\n\t" );
    /*REG_WRITE(0x00140520, 0x0f000009);*/asm volatile("li t0, 0x0f000009\n\t" "li t1, 0x00140520\n\t" "sw t0, 0x0(t1)\n\t" );
    /*REG_WRITE(0x00140524, 0x00000309);*/asm volatile("li t0, 0x00000309\n\t" "li t1, 0x00140524\n\t" "sw t0, 0x0(t1)\n\t" );
    /*REG_WRITE(0x00140710, 0x0e00003c);*/asm volatile("li t0, 0x0e00003c\n\t" "li t1, 0x00140710\n\t" "sw t0, 0x0(t1)\n\t" );
    /*REG_WRITE(0x00140810, 0x0e00003c);*/asm volatile("li t0, 0x0e00003c\n\t" "li t1, 0x00140810\n\t" "sw t0, 0x0(t1)\n\t" );
    /*REG_WRITE(0x00140910, 0x0e00003c);*/asm volatile("li t0, 0x0e00003c\n\t" "li t1, 0x00140910\n\t" "sw t0, 0x0(t1)\n\t" );
    /*REG_WRITE(0x00140A10, 0x0e00003c);*/asm volatile("li t0, 0x0e00003c\n\t" "li t1, 0x00140A10\n\t" "sw t0, 0x0(t1)\n\t" );
    /*REG_WRITE(0x00140B10, 0x0e00003c);*/asm volatile("li t0, 0x0e00003c\n\t" "li t1, 0x00140B10\n\t" "sw t0, 0x0(t1)\n\t" );
    /*REG_WRITE(0x00140C10, 0x0e00003c);*/asm volatile("li t0, 0x0e00003c\n\t" "li t1, 0x00140C10\n\t" "sw t0, 0x0(t1)\n\t" );
    /*REG_WRITE(0x00140D10, 0x0e00003c);*/asm volatile("li t0, 0x0e00003c\n\t" "li t1, 0x00140D10\n\t" "sw t0, 0x0(t1)\n\t" );
    /*REG_WRITE(0x00140E10, 0x0e00003c);*/asm volatile("li t0, 0x0e00003c\n\t" "li t1, 0x00140E10\n\t" "sw t0, 0x0(t1)\n\t" );
    /*REG_WRITE(0x00140200, 0x3000b0c7);*/asm volatile("li t0, 0x3000b0c7\n\t" "li t1, 0x00140200\n\t" "sw t0, 0x0(t1)\n\t" );
    /*REG_WRITE(0x0014052C, 0x0fc00172);*/asm volatile("li t0, 0x0fc00172\n\t" "li t1, 0x0014052C\n\t" "sw t0, 0x0(t1)\n\t" );
    /*REG_WRITE(0x00140100, 0x2800040c);*/asm volatile("li t0, 0x2800040c\n\t" "li t1, 0x00140100\n\t" "sw t0, 0x0(t1)\n\t" );
    /*REG_WRITE(0x00140088, 0x20c01884);*/asm volatile("li t0, 0x20c01884\n\t" "li t1, 0x00140088\n\t" "sw t0, 0x0(t1)\n\t" );
    /*REG_WRITE(0x00140040, 0x5e001810);*/asm volatile("li t0, 0x5e001810\n\t" "li t1, 0x00140040\n\t" "sw t0, 0x0(t1)\n\t" );
    /*REG_WRITE(0x00140044, 0x008005f0);*/asm volatile("li t0, 0x008005f0\n\t" "li t1, 0x00140044\n\t" "sw t0, 0x0(t1)\n\t" );
    /*REG_WRITE(0x00140180, 0x00000a31);*/asm volatile("li t0, 0x00000a31\n\t" "li t1, 0x00140180\n\t" "sw t0, 0x0(t1)\n\t" );
    /*REG_WRITE(0x00140184, 0x00000001);*/asm volatile("li t0, 0x00000001\n\t" "li t1, 0x00140184\n\t" "sw t0, 0x0(t1)\n\t" );
    /*REG_WRITE(0x00140188, 0x00000018);*/asm volatile("li t0, 0x00000018\n\t" "li t1, 0x00140188\n\t" "sw t0, 0x0(t1)\n\t" );
    /*REG_WRITE(0x0014018C, 0x00000200);*/asm volatile("li t0, 0x00000200\n\t" "li t1, 0x0014018C\n\t" "sw t0, 0x0(t1)\n\t" );
    /*REG_WRITE(0x00140190, 0x00000000);*/asm volatile("li t0, 0x00000000\n\t" "li t1, 0x00140190\n\t" "sw t0, 0x0(t1)\n\t" );
    /*REG_WRITE(0x00140194, 0x00000640);*/asm volatile("li t0, 0x00000640\n\t" "li t1, 0x00140194\n\t" "sw t0, 0x0(t1)\n\t" );
    /*REG_WRITE(0x00140200, 0x3000b0c7);*/asm volatile("li t0, 0x3000b0c7\n\t" "li t1, 0x00140200\n\t" "sw t0, 0x0(t1)\n\t" );
    /*REG_WRITE(0x00140198, 0x00000800);*/asm volatile("li t0, 0x00000800\n\t" "li t1, 0x00140198\n\t" "sw t0, 0x0(t1)\n\t" );
    /*REG_WRITE(0x00140110, 0x0627100a);*/asm volatile("li t0, 0x0627100a\n\t" "li t1, 0x00140110\n\t" "sw t0, 0x0(t1)\n\t" );
    /*REG_WRITE(0x00140114, 0x281a0408);*/asm volatile("li t0, 0x281a0408\n\t" "li t1, 0x00140114\n\t" "sw t0, 0x0(t1)\n\t" );
    /*REG_WRITE(0x00140118, 0x00070380);*/asm volatile("li t0, 0x00070380\n\t" "li t1, 0x00140118\n\t" "sw t0, 0x0(t1)\n\t" );
    /*REG_WRITE(0x0014011C, 0x02000101);*/asm volatile("li t0, 0x02000101\n\t" "li t1, 0x0014011C\n\t" "sw t0, 0x0(t1)\n\t" );
    /*REG_WRITE(0x00140120, 0x01cd0608);*/asm volatile("li t0, 0x01cd0608\n\t" "li t1, 0x00140120\n\t" "sw t0, 0x0(t1)\n\t" );
    /*REG_WRITE(0x00140124, 0x0036100a);*/asm volatile("li t0, 0x0036100a\n\t" "li t1, 0x00140124\n\t" "sw t0, 0x0(t1)\n\t" );
    /*REG_WRITE(0x00140014, 0x020046a0);*/asm volatile("li t0, 0x020046a0\n\t" "li t1, 0x00140014\n\t" "sw t0, 0x0(t1)\n\t" );
    /*REG_WRITE(0x00140018, 0x20006c2b);*/asm volatile("li t0, 0x20006c2b\n\t" "li t1, 0x00140018\n\t" "sw t0, 0x0(t1)\n\t" );
    /*REG_WRITE(0x0014001C, 0xc0aa0060);*/asm volatile("li t0, 0xc0aa0060\n\t" "li t1, 0x0014001C\n\t" "sw t0, 0x0(t1)\n\t" );
    /*REG_WRITE(0x0014002C, 0x80040000);*/asm volatile("li t0, 0x80040000\n\t" "li t1, 0x0014002C\n\t" "sw t0, 0x0(t1)\n\t" );
    /*REG_WRITE(0x00140004, 0x00000073);*/asm volatile("li t0, 0x00000073\n\t" "li t1, 0x00140004\n\t" "sw t0, 0x0(t1)\n\t" );
	//phy init
	rd_data = 0x0;
    while (rd_data != 0x8000000f ){ 
    rd_data = readl(0x00140034);
    }
	//phy SDRAM config
    /*REG_WRITE(0x00140004, 0x00040001);*/asm volatile("li t0, 0x00040001\n\t" "li t1, 0x00140004\n\t" "sw t0, 0x0(t1)\n\t" );
	//phy SDRAM init
	rd_data = 0x0;
    while (rd_data != 0x8000001f ){ 
    rd_data = readl(0x00140034);
    }
	//mc SDRAM config
    /*REG_WRITE(0x001301b0, 0x00000041);*/asm volatile("li t0, 0x00000041\n\t" "li t1, 0x001301b0\n\t" "sw t0, 0x0(t1)\n\t" );
    /*REG_WRITE(0x00130320, 0x00000001);*/asm volatile("li t0, 0x00000001\n\t" "li t1, 0x00130320\n\t" "sw t0, 0x0(t1)\n\t" );
	//mc SDRAM init
	rd_data = 0x0;
    while ((rd_data&0x1) == 0 ){ 
    rd_data = readl(0x00130004);
    }
    // mc SDRAM config reset
    /*REG_WRITE(0x00130320, 0x00000000);*/asm volatile("li t0, 0x00000000\n\t" "li t1, 0x00130320\n\t" "sw t0, 0x0(t1)\n\t" );
    /*REG_WRITE(0x00130060, 0x00000001);*/asm volatile("li t0, 0x00000001\n\t" "li t1, 0x00130060\n\t" "sw t0, 0x0(t1)\n\t" );
    /*REG_WRITE(0x001301b0, 0x00000040);*/asm volatile("li t0, 0x00000040\n\t" "li t1, 0x001301b0\n\t" "sw t0, 0x0(t1)\n\t" );
    /*REG_WRITE(0x00130320, 0x00000001);*/asm volatile("li t0, 0x00000001\n\t" "li t1, 0x00130320\n\t" "sw t0, 0x0(t1)\n\t" );
    /*REG_WRITE(0x00130010, 0x00001010);*/asm volatile("li t0, 0x00001010\n\t" "li t1, 0x00130010\n\t" "sw t0, 0x0(t1)\n\t" );
    /*REG_WRITE(0x00130014, 0x00000181);*/asm volatile("li t0, 0x00000181\n\t" "li t1, 0x00130014\n\t" "sw t0, 0x0(t1)\n\t" );
    /*REG_WRITE(0x00130010, 0x80001010);*/asm volatile("li t0, 0x80001010\n\t" "li t1, 0x00130010\n\t" "sw t0, 0x0(t1)\n\t" );
    // write leveling config
    /*REG_WRITE(0x00140314, 0x000000ff);*/asm volatile("li t0, 0x000000ff\n\t" "li t1, 0x00140314\n\t" "sw t0, 0x0(t1)\n\t" );
    /*REG_WRITE(0x001404DC, 0x00000000);*/asm volatile("li t0, 0x00000000\n\t" "li t1, 0x001404DC\n\t" "sw t0, 0x0(t1)\n\t" );
    /*REG_WRITE(0x00140098, 0x00010000);*/asm volatile("li t0, 0x00010000\n\t" "li t1, 0x00140098\n\t" "sw t0, 0x0(t1)\n\t" );
    /*REG_WRITE(0x00140004, 0x00000201);*/asm volatile("li t0, 0x00000201\n\t" "li t1, 0x00140004\n\t" "sw t0, 0x0(t1)\n\t" );
	
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
    /*REG_WRITE(0x00130010, 0x00001010);*/asm volatile("li t0, 0x00001010\n\t" "li t1, 0x00130010\n\t" "sw t0, 0x0(t1)\n\t" );
    /*REG_WRITE(0x00130014, 0x00000101);*/asm volatile("li t0, 0x00000101\n\t" "li t1, 0x00130014\n\t" "sw t0, 0x0(t1)\n\t" );
    /*REG_WRITE(0x00130010, 0x80001010);*/asm volatile("li t0, 0x80001010\n\t" "li t1, 0x00130010\n\t" "sw t0, 0x0(t1)\n\t" );
    // read & write training config
    /*REG_WRITE(0x00140004, 0x0002fc01);*/asm volatile("li t0, 0x0002fc01\n\t" "li t1, 0x00140004\n\t" "sw t0, 0x0(t1)\n\t" );
	// read & write training
	rd_data = 0x0;
    while (rd_data != 0x80004fff ){ 
    rd_data = readl(0x00140034);
    }
    // mc final config
    /*REG_WRITE(0x00130320, 0x00000000);*/asm volatile("li t0, 0x00000000\n\t" "li t1, 0x00130320\n\t" "sw t0, 0x0(t1)\n\t" );
    /*REG_WRITE(0x00130060, 0x00000000);*/asm volatile("li t0, 0x00000000\n\t" "li t1, 0x00130060\n\t" "sw t0, 0x0(t1)\n\t" );
    /*REG_WRITE(0x00130320, 0x00000001);*/asm volatile("li t0, 0x00000001\n\t" "li t1, 0x00130320\n\t" "sw t0, 0x0(t1)\n\t" );
    /*REG_WRITE(0x00130490, 0x00000001);*/asm volatile("li t0, 0x00000001\n\t" "li t1, 0x00130490\n\t" "sw t0, 0x0(t1)" );
#endif
}
