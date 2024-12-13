#ifndef __SDMMC_COMMON_H__
#define __SDMMC_COMMON_H__
#include "asm/type.h"

#define EMMC_BASE	0x1200000
#define SDMMC_BASE	0x1200000

static inline unsigned long mmio_wr8(unsigned long addr, u8 value)
{
    //*(volatile u8*)addr = value;
    //tangdan
    *(volatile u8*)((unsigned long long)addr) = value;
    return 0;
}

static inline u8 mmio_rd8(unsigned long addr)
{
    //return *(volatile u8*)addr;
    return *(volatile u8*)((unsigned long long)addr);
}

static inline unsigned long mmio_wr16(unsigned long addr, u16 value)
{
    //*(volatile u16*)addr = value;
    *(volatile u16*)((unsigned long long)addr) = value;
    return 0;
}

static inline u16 mmio_rd16(unsigned long addr)
{
    //return *(volatile u16*)addr;
    return *(volatile u16*)((unsigned long long)addr);
}

static inline unsigned long mmio_wr32(unsigned long addr, u32 value)
{
    //*(volatile u32*)addr = value;
    *(volatile u32*)((unsigned long long)addr) = value;
    return 0;
}

static inline u32 mmio_rd32(unsigned long addr)
{
    //return *(volatile u32*)addr;
    return *(volatile u32*)((unsigned long long)addr);
}

static inline unsigned long mmio_wr64(unsigned long addr, u64 value)
{
    //*(volatile u64*)addr = value;
    *(volatile u64*)((unsigned long long)addr) = value;
    return 0;
}

static inline u64 mmio_rd64(unsigned long addr)
{
    //return *(volatile u64*)addr;
    return *(volatile u64*)((unsigned long long)addr);
}

//static inline char read_chk_16 (unsigned long* addr, u16 exp_data, u16 msk)
//{
//    u16 tmp_val;
//
//    tmp_val = mmio_rd16(addr);
//    if((tmp_val&~msk)==(exp_data&~msk))
//    {
//        return 1;
//    }
//    else
//    {
//        //mmio_wr32(TERM_SIM_ADDR,0x0B0B0B0B);     // indicate sim failed
//        //printf("read chk fail ! addr %x exp %x act %x mask %x", addr, exp_data, tmp_val, msk);
//        return 0;
//    }
//}
//
//
//static inline char read_chk (unsigned long* addr, u32 exp_data, u32 msk)
//{
//    u32 tmp_val;
//
//    tmp_val = mmio_rd32(addr);
//    if((tmp_val&~msk)==(exp_data&~msk))
//    {
//        return 1;
//    }
//    else
//    {
//        //mmio_wr32(TERM_SIM_ADDR,0x0B0B0B0B);     // indicate sim failed
//        //printf("read chk fail ! addr %x exp %x act %x mask %x", addr, exp_data, tmp_val, msk);
//        return 0;
//    }
//}
//
//static inline char read_chk_64 (unsigned long* addr, u64 exp_data, uint64_t msk)
//{
//    u64 tmp_val;
//
//    tmp_val = mmio_rd64(addr);
//    if((tmp_val&~msk)==(exp_data&~msk))
//    {
//        return 1;
//    }
//    else
//    {
//        //mmio_wr32(TERM_SIM_ADDR,0x0B0B0B0B);     // indicate sim failed
//        //printf("read chk fail ! addr %x exp %x act %x mask %x", addr, exp_data, tmp_val, msk);
//        return 0;
//    }
//}

static inline unsigned long wait(int max)
{
    while(max--)
    {
        __asm__ volatile ("nop");
    }
    return 0;
}

///static inline char polling(unsigned long* addr, u32 exp_data, u32 msk)
///{
/// u32 tmp_val;
/// char tmp_flag = 1;
///
///     while(tmp_flag)
///     {
///			 tmp_val = mmio_rd32(addr);
/// 			 if((tmp_val&~msk)==(exp_data&~msk))
///    	 {
///           tmp_flag = 0;
///       }
///   	 }
///   return 1;
///}
///
///
///static inline char poll2ing (unsigned long* addr, u32 exp_data, u32 biten, u32 lsb)
///{
///    u32  tmp_val;
///    char tmp_flag = 1;
///
///    while(tmp_flag)
///    {
///        tmp_val = mmio_rd32(addr);
///        if(((tmp_val&biten)>>lsb)>=(exp_data))
///        {
///            tmp_flag = 0;
///        }
///    }
///    return 1;
///}


char read_chk_16 (unsigned long addr, u16 exp_data, u16 msk);
char read_chk (unsigned long addr, u32 exp_data, u32 msk);
char read_chk_64 (unsigned long addr, u64 exp_data, u64 msk);

void polling_byte_mhsc(u32 offset, u32 mask, u32 expect);
void card_detection(void);
void set_clock(u32 div);
void host_controller_setup(void);
void wait_command_complete(void);
void sdma_write_test(u32 axi_addr_high, u32 axi_addr_low, u32 block_size, u32 block_cnt, u32 card_addr);
void sdma_read_test(u32 axi_addr_high, u32 axi_addr_low, u32 block_size, u32 block_cnt, u32 card_addr);
void check_rd32(u32 addr, u32 expected);
void check_rd(u32 addr_width, u64 addr, u32 expected);
u32 send_CMD_R1R3(u32 cmd_index, u32 argument);
u32 send_CMD_R2(u32 cmd_index, u32 argument);
void send_CMD0(void);
void sdmmc_init(void);

#endif
