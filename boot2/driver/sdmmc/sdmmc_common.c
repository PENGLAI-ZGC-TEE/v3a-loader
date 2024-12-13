#ifndef __SDMMC_COMMON_C__
#define __SDMMC_COMMON_C__

#include "sdmmc/common.h"
#include "sdmmc/sdmmc_common.h"
char read_chk_16 (unsigned long addr, u16 exp_data, u16 msk)
{
    u16 tmp_val;

    tmp_val = mmio_rd16(addr);
    if((tmp_val&~msk)==(exp_data&~msk))
    {
        return 1;
    }
    else
    {
        my_print("read chk fail ! addr %x exp %x act %x mask %x", addr, exp_data, tmp_val, msk);
        return 0;
    }
}


char read_chk (unsigned long addr, u32 exp_data, u32 msk)
{
    u32 tmp_val;

    tmp_val = mmio_rd32(addr);
    if((tmp_val&~msk)==(exp_data&~msk))
    {
        return 1;
    }
    else
    {
        my_print("read chk fail ! addr %x exp %x act %x mask %x", addr, exp_data, tmp_val, msk);
        return 0;
    }
}

char read_chk_64 (unsigned long addr, u64 exp_data, u64 msk)
{
    u64 tmp_val;

    tmp_val = mmio_rd64(addr);
    if((tmp_val&~msk)==(exp_data&~msk))
    {
        return 1;
    }
    else
    {
        my_print("read chk fail ! addr %x exp %x act %x mask %x", addr, exp_data, tmp_val, msk);
        return 0;
    }
}


void polling_byte_mhsc(u32 offset, u32 biten, u32 expect){
    u32 rdata;
    do{
        rdata = mmio_rd32(SDMMC_BASE+offset) & biten;
    } while (rdata != expect);
}


void card_detection(void){
    u32 rdata;
    // Enable interrupt
    mmio_wr8(SDMMC_BASE+0x34,0xc0);
    // Enable interrupt
    mmio_wr8(SDMMC_BASE+0x38,0xc0);
    // Wait card insertion
    do {
       rdata = mmio_rd32(SDMMC_BASE+0x24)&0x030000;
    } while (rdata!=0x030000);
    // Clear card insertion interrupt
    mmio_wr8(SDMMC_BASE+0x30,0x40);
}

void send_CMD0(void){
    polling_byte_mhsc(0x24, 0x01, 0x00); //wait until CMD_INHABIT==0

    // Set command argument
    mmio_wr32(SDMMC_BASE+0x08,0);

    // Set CMD
    // [13:8] CMD_INDEX
    // [7:6] CMD TYPE, 0x0:Normal, 0x1:Suspend, 0x2:Resume, 0x3:Abort
    // [4] CMD_INDEX check enable
    // [3] CRC check enable
    // [1:0] Response type, 0x0: NO_RESP, 0x1: RESP length 136, 0x2: RESP length 48
    mmio_wr16(SDMMC_BASE+0xe,(0<<8)+0x0000);

    polling_byte_mhsc(0x30, 0x01, 0x01); // NORMAL_INT_STAT_R[0] CMD_COMPLETE
    mmio_wr16(SDMMC_BASE+0x30,0x0001); // clear CMD_COMPLETE interrupt

    //rdata = mmio_rd32(SDMMC_BASE+0x10); // RESP01_R
    //return rdata;
}

u32 send_CMD_R1R3(u32 cmd_index, u32 argument ){
    u32 rdata;
    polling_byte_mhsc(0x24, 0x01, 0x00); //wait until CMD_INHABIT==0

    // Set command argument
    mmio_wr32(SDMMC_BASE+0x08,argument);

    // Set CMD
    // [13:8] CMD_INDEX
    // [7:6] CMD TYPE, 0x0:Normal, 0x1:Suspend, 0x2:Resume, 0x3:Abort
    // [4] CMD_INDEX check enable
    // [3] CRC check enable
    // [1:0] Response type, 0x0: NO_RESP, 0x1: RESP length 136, 0x2: RESP length 48
    mmio_wr16(SDMMC_BASE+0xe,(cmd_index<<8)+0x0002);

    polling_byte_mhsc(0x30, 0x01, 0x01); // NORMAL_INT_STAT_R[0] CMD_COMPLETE
    mmio_wr16(SDMMC_BASE+0x30,0x0001); // clear CMD_COMPLETE interrupt

    rdata = mmio_rd32(SDMMC_BASE+0x10); // RESP01_R

    return rdata;
}

u32 send_CMD_R2(u32 cmd_index, u32 argument ){
    u32 rdata;
    polling_byte_mhsc(0x24, 0x01, 0x00); //wait until CMD_INHABIT==0

    // Set command argument
    mmio_wr32(SDMMC_BASE+0x08,argument);

    // Set CMD
    // [13:8] CMD_INDEX
    // [7:6] CMD TYPE, 0x0:Normal, 0x1:Suspend, 0x2:Resume, 0x3:Abort
    // [4] CMD_INDEX check enable
    // [3] CRC check enable
    // [1:0] Response type, 0x0: NO_RESP, 0x1: RESP length 136, 0x2: RESP length 48
    mmio_wr16(SDMMC_BASE+0xe,(cmd_index<<8)+0x0001);//136-bit

    polling_byte_mhsc(0x30, 0x01, 0x01); // NORMAL_INT_STAT_R[0] CMD_COMPLETE
    mmio_wr16(SDMMC_BASE+0x30,0x0001); // clear CMD_COMPLETE interrupt

    rdata = mmio_rd32(SDMMC_BASE+0x10); // TBD: return partial response RESP01_R

    return rdata;
}

void set_clock(u32 div){
    u32 rdata;
    //---- Clock control
    mmio_wr16(SDMMC_BASE+0x2c,(div<<8)+0x01); // SD CLK  [15:8]=div, freq=200MHz/(div*2)
    mmio_wr8(SDMMC_BASE+0x2c,0x01);
    mmio_wr8(SDMMC_BASE+0x2c,0x0b);
        
    do { // wait clock stable
       rdata = mmio_rd8(SDMMC_BASE+0x2c)&0x02;  // wait until 0x2c[1]==1
    } while (!(rdata==0x02));

    // Eable clock
    mmio_wr8(SDMMC_BASE+0x2c,0x03);
    
    do { // wait clock stable
       rdata = mmio_rd8(SDMMC_BASE+0x2c)&0x02;  // wait until 0x2c[1]==1
    } while (!(rdata==0x02));
    mmio_wr8(SDMMC_BASE+0x2c,0x0b);
    // Output SDCLK
    mmio_wr8(SDMMC_BASE+0x2c,0x0f);
    
}

void host_controller_setup(void){
    u32 rdata;
    //---- Power control
    // PWR_CTRL_R
    mmio_wr8(SDMMC_BASE+0x29,0x0e);
    // set power control
    mmio_wr8(SDMMC_BASE+0x29,0xbe);
    // TOUT_CTRL_R: set timeout counter
    mmio_wr8(SDMMC_BASE+0x2e,0x00);
    // set power control
    mmio_wr8(SDMMC_BASE+0x29,0xbf);

    //---- Card is EMMC
    u32 VENDOR_ID;
    VENDOR_ID = mmio_rd16(SDMMC_BASE+0xe8);
    my_print("VENDOR_ID = 0x%0x\n",VENDOR_ID);
    // Set EMMC control register: assert emmc_rst_n(sd_rst_n)
    mmio_wr8(SDMMC_BASE+VENDOR_ID+0x2c,0x09);
    // Set EMMC control register
    mmio_wr8(SDMMC_BASE+VENDOR_ID+0x2c,0x0d); // to tell MHSC CARD_IS_EMMC   
    // Set EMMC clock div for pass simulation. (delay line deafult select will cause simulation hang)
    mmio_wr16(SDMMC_BASE+VENDOR_ID+0x2c,0x020d);

    set_clock(0x01); //set dividend

    //---- Reset control
    // EMMC_RESET
    mmio_wr8(SDMMC_BASE+0x2f,0x02);
    // Check the EMMC_RESET
    do {
       rdata = mmio_rd8(SDMMC_BASE+0x2f)&0x02;
    } while (rdata);
    // Reset DAT line
    mmio_wr8(SDMMC_BASE+0x2f,0x04);
    // Check the Reset DAT Line
    do {
       rdata = mmio_rd8(SDMMC_BASE+0x2f)&0x04;
    } while (rdata);

    //Enable all interrupt
    mmio_wr8(SDMMC_BASE+0x34,0xff);
    //Enable all interrupt
    mmio_wr8(SDMMC_BASE+0x38,0xfb);
    //Enable error interrupt
    mmio_wr8(SDMMC_BASE+0x36,0xff);
    //Enable error interrupt
    mmio_wr8(SDMMC_BASE+0x3a,0xff);

    // Auto tuning control
    mmio_wr8(SDMMC_BASE+VENDOR_ID+0x40,0x1d);
//  mmio_wr32(SDMMC_BASE+VENDOR_ID+0x40,0x1f030004) ; // match host testbench example

}

void wait_command_complete(void){
    polling_byte_mhsc(0x30, 0x01, 0x01); // NORMAL_INT_STAT_R[0] CMD_COMPLETE
    mmio_wr16(SDMMC_BASE+0x30,0x0001); // clear CMD_COMPLETE interrupt
}


void sdma_write_test(u32 axi_addr_high, u32 axi_addr_low, u32 block_size, u32 block_cnt, u32 card_addr)
{
    //--------------------------------------
    // SDMA - WRITE
    //--------------------------------------
    // Set control register : SDMA
    // HOST_CTRL1_R
    // [4:3] DMA_SEL, 0x0: SDMA, 0x2: ADMA2, 0x3:ADMA3
    // [2] HIGH_SPEED_EN
    // [1] DAT_XFER_WIDTH, 0x0: 1-bit mode, 0x1: 4-bit mode
    // [0] LED_CTRL
    mmio_wr8(SDMMC_BASE+0x28,0x02);

    // ADMA_SA_LOW
    mmio_wr32(SDMMC_BASE+0x58,axi_addr_low); // AXI ADDR[31:0]
    // ADMA_SA_HIGH
    mmio_wr32(SDMMC_BASE+0x5c,axi_addr_high); // AXI ADDR[64:32]

    // BLOCK SIZE
    // [11:0] Xfer block size in bytes, 0x40:64 bytes, 0x200: 512 bytes
    // [14:12] SDMA buffer boundary, 0x0:4K bytes bound, 0x1:8K bytes bound, 0x2:16K bytes bound
    mmio_wr16(SDMMC_BASE+0x4,0x5000+block_size);
    
    // SDMASA count
    mmio_wr32(SDMMC_BASE+0x0,block_cnt);
    
    // BLOCK_COUNT
    //mmio_wr16(SDMMC_BASE+0x6, 4); // STOP count
    
    // ARGUMENT
    mmio_wr32(SDMMC_BASE+0x8,card_addr); // address

    // XFER_MODE
    // [5] Multi-block select
    // [4] Data Transfer Direction, 0x1: READ(Card to Host), 0x0 WRITE(Host to Card)
    // [3:2] Auto-command enable
    // [1] BLOCK_COUNT enable
    // [0] DMA enable
    mmio_wr16(SDMMC_BASE+0xc,0x0027); // WRITE

    // Set CMD
    // [13:8] CMD_INDEX
    // [7:6] CMD TYPE, 0x0:Normal, 0x1:Suspend, 0x2:Resume, 0x3:Abort
    // [4] CMD_INDEX check enable
    // [3] CRC check enable
    // [1:0] Response type, 0x0: NO_RESP, 0x1: RESP length 136, 0x2: RESP length 48
    mmio_wr16(SDMMC_BASE+0xe,0x193a); // CMD25, WRITE multiple block

    wait_command_complete();

    // wait for transfer complete
    polling_byte_mhsc(0x30, 0x02, 0x02); // NORMAL_INT_STAT_R[0] XFER_COMPLETE
    mmio_wr16(SDMMC_BASE+0x30,0x0002); // clear DMA_INTERRUPT and XFER_COMPLETE interrupt
}

/*
void sdma_read_test(u32 axi_addr_high, u32 axi_addr_low, u32 block_size, u32 block_cnt, u32 card_addr){

    //--------------------------------------
    // SDMA - READ
    //--------------------------------------
    // Set control register : SDMA
    // HOST_CTRL1_R
    // [4:3] DMA_SEL, 0x0: SDMA, 0x2: ADMA2, 0x3:ADMA3
    // [2] HIGH_SPEED_EN
    // [1] DAT_XFER_WIDTH, 0x0: 1-bit mode, 0x1: 4-bit mode
    // [0] LED_CTRL
    mmio_wr8(SDMMC_BASE+0x28,0x02);

    // ADMA_SA_LOW
    mmio_wr32(SDMMC_BASE+0x58,axi_addr_low); // AXI ADDR[31:0]
    // ADMA_SA_HIGH
    mmio_wr32(SDMMC_BASE+0x5c,axi_addr_high); // AXI ADDR[64:32]

    // BLOCK SIZE
    // [11:0] Xfer block size in bytes
    // [14:12] SDMA buffer boundary, 0x0:4K bytes bound, 0x1:8K bytes bound, 0x2:16K bytes bound
    mmio_wr16(SDMMC_BASE+0x4,0x5000+block_size);

    // SDMASA count
    mmio_wr32(SDMMC_BASE+0x0,block_cnt);
    
    // BLOCK_COUNT
    //mmio_wr16(SDMMC_BASE+0x6, 0); // STOP count
    
    // ARGUMENT
    mmio_wr32(SDMMC_BASE+0x8,card_addr); // address

    // XFER_MODE
    // [5] Multi-block select
    // [4] Data Transfer Direction, 0x1: READ(Card to Host), 0x0 WRITE(Host to Card)
    // [3:2] Auto-command enable
    // [1] BLOCK_COUNT enable
    // [0] DMA enabler
    mmio_wr16(SDMMC_BASE+0xc,0x0037); // READ

    // Set CMD
    // [13:8] CMD_INDEX
    // [7:6] CMD TYPE, 0x0:Normal, 0x1:Suspend, 0x2:Resume, 0x3:Abort
    // [4] CMD_INDEX check enable
    // [3] CRC check enable
    // [1:0] Response type, 0x0: NO_RESP, 0x1: RESP length 136, 0x2: RESP length 48
    mmio_wr16(SDMMC_BASE+0xe,0x123a); // CMD18, READ multiple block

    wait_command_complete();

    // wait for transfer complete
    polling_byte_mhsc(0x30, 0x02, 0x02); // NORMAL_INT_STAT_R[0] XFER_COMPLETE
    mmio_wr16(SDMMC_BASE+0x30,0x0002); // clear DMA_INTERRUPT and XFER_COMPLETE interrupt
} 
*/
void check_rd32(u32 addr, u32 expected){
    u32 rdata;

    rdata = mmio_rd32(addr);

    if(rdata!=expected){
        my_print("read chk fail ! addr %x exp %x act %x", addr, expected, rdata);
        //mmio_wr32(TERM_SIM_ADDR,0x0B0B0B0B); // fail
    }
}

void check_rd(u32 addr_width, u64 addr, u32 expected){
    u32 rdata;

    rdata = addr_width==32 ? mmio_rd32(addr) :
            addr_width==64 ? mmio_rd64(addr) : 0;

    if(rdata!=expected)
        my_print("read chk fail ! addr %x exp %x act %x",addr,expected,rdata);
}

#endif
