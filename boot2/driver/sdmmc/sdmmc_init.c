#include "print.h"
#include "sdmmc/common.h"
#include "sdmmc/sdmmc_common.h"
unsigned int err_flag=0;
void delay(int num)
{
   for(int i=0; i < num*2; i++){};	   
}

void sdmmc_init()
{ 
    int i=0;
    unsigned int resp01 = 0;
    unsigned int resp23 = 0;
    unsigned int resp45 = 0;
    unsigned int resp67 = 0;
    
    my_print("sdmmc test begin! \r\n");

    delay(1000);
    
    mmio_wr32(EMMC_BASE+0x2c,0);
  
    //-------------------------------------------------
    // Card Insert Sequence
    //-------------------------------------------------
    card_detection();
    my_print("Card Inserted Decteced \r\n");
    
    //-------------------------------------------------
    // Host Controller Setup Sequence
    //-------------------------------------------------
    host_controller_setup();
    resp45 = mmio_rd32(EMMC_BASE+0x29); //REG_READ(0x30050018);
    resp45 &= ~0xf;
    resp45 |=0xb;
    mmio_wr32(EMMC_BASE+0x29,resp45);
    my_print("Host Controller Setup Done \r\n");

    //Dummy read to let 1st cmd is sent at least after 74 clock cycles
    for(i=0;i<20;i++) {
      mmio_rd8(EMMC_BASE+0x2c);  //dummy  read
    }

    //OST_CTRL_2_R
    //set to Version 4
    //set to HS SDR
    mmio_wr16(EMMC_BASE+0x3e, 0x7401); //??? 7400???

    //-------------------------------------------------
    // Initialize EMMC
    //-------------------------------------------------
    //send cmd0
    send_CMD0();
    my_print("send CMD0 \r\n");

    //send cmd1
    resp01 = send_CMD_R1R3(1, 0x00ff8080);
    while((resp01 & 0x80000000) == 0) {
      resp01 = send_CMD_R1R3(1, 0x00ff8080);
    }
    my_print("send CMD R1R3 \r\n");
    if(resp01 !=  0x80ff8080) {
      my_print("cmd1 resp error ! exp 80ff8080 act %x", resp01);
      err_flag++;
    }
  
    //send cmd2
    resp01 = send_CMD_R2(2, 0);
    resp01 = mmio_rd32(EMMC_BASE+0x10); //REG_READ(0x30050010);
    resp23 = mmio_rd32(EMMC_BASE+0x14); //REG_READ(0x30050014);
    resp45 = mmio_rd32(EMMC_BASE+0x18); //REG_READ(0x30050018);
    resp67 = mmio_rd32(EMMC_BASE+0x1c); //REG_READ(0x3005001c);
    if((resp01 != 0x01234567) | (resp23 != 0x89abcdef)|
       (resp45 != 0x11234456) | (resp67 != 0x0099abcd)) {
      my_print("cmd2 resp error ! resp %08x %08x %08x %08x", resp01, resp23, resp45, resp67);
      err_flag++;
    }
    my_print("send CMD 2 done \r\n");

    //send cmd3, set RCA = 0x1
    resp01 = send_CMD_R1R3(3, 0x00010000);
    if(resp01 !=  0xabcd0000) {
      my_print("cmd3 resp error ! exp abcd0000 act %x", resp01);
      err_flag++;
    }
    my_print("send CMD R1R3 2 \r\n");
  
    //send cmd7, select card
    resp01 = send_CMD_R1R3(7, 0x00010000);
    if(resp01 !=  0x00000b00) {
      my_print("cmd3 resp error ! exp 000b0000 act %x", resp01);
      err_flag++;
    }
    my_print("send CMD R1R  7 \r\n");
 
    //send cmd7, deselect card
    resp01 = send_CMD_R1R3(7, 0x00000000);
    if(resp01 !=  0x00000b00) {
      my_print("cmd3 resp error ! exp 000b0000 act %x", resp01);
      err_flag++;
    }

    //card removal
    polling_byte_mhsc(0x30, 0x80, 0x80); //CARD_REMOVAL_INT
    mmio_wr16(EMMC_BASE+0x30,0x0080); // clear CARD_REMOVAL interrupt
    my_print("Card Removal\n");

    my_print("sdmmc test done!");
    if(err_flag == 0)
      *(volatile unsigned int*)(UART_BASE+0xcc) = 0xa;
    else
      *(volatile unsigned int*)(UART_BASE+0xcc) = 0x5;
}

