#include <qspi.h>

#define REG32(addr)       (*((volatile unsigned int *)(addr)))
#define QSPI_BASE_ADDR   (0xa0000)

/* trigger flash to exit xip mode*/
static void qspi_trigger_flash()
{
	unsigned int status = 0x2;
	REG32(QSPI_BASE_ADDR + 0x90) = 0xb5b00001; // read novolatile register
	while(status){
		status =  REG32(QSPI_BASE_ADDR + 0x90);
		status &= 0x2;
	}
	REG32(QSPI_BASE_ADDR + 0x90) = 0xb5b00001;
	status = 2;
	while(status){
		status =  REG32(QSPI_BASE_ADDR + 0x90);
		status &= 0x2;
	}
}

static void wait_cmd_reg(void)
{
	unsigned int status = 2;
	while(status){
		status =  REG32(QSPI_BASE_ADDR + 0x90);
		status &= 0x2;
	}
}

static void wait_device_not_busy(void)
{
	unsigned int f_st = 1;
	/*read status reg*/
	while(f_st){
		REG32(QSPI_BASE_ADDR + 0x90) = 0x5800001;
		wait_cmd_reg( );
		f_st =  REG32(QSPI_BASE_ADDR + 0xa0);
		f_st &= 0x1;
	}
}
/*
 *enable flash address writalbe permission
 *exit flash and qspi xip mode
 */
void qspi_init()
{
	REG32(QSPI_BASE_ADDR) = 0x80180081;// disable xip mode
	REG32(QSPI_BASE_ADDR + 0x4) = 0x0; // read config register to 0x0
	qspi_trigger_flash();
	REG32(QSPI_BASE_ADDR + 0x4) = 0x0a0222ec; // for read config
	qspi_trigger_flash();
	/*config device write instruction register*/
	REG32(QSPI_BASE_ADDR + 0x8) = 0x22012;
}

void qspi_nonv_cfg(unsigned int data)
{
	REG32(QSPI_BASE_ADDR + 0xa8) = data;
	/*write enable*/
	REG32(QSPI_BASE_ADDR + 0x90) = 0x06000001;
	wait_cmd_reg();
	/*write data to reg*/
	REG32(QSPI_BASE_ADDR + 0x90) = 0xB1009001;
	wait_cmd_reg();
	if(data == 0xa8f6){
		REG32(QSPI_BASE_ADDR + 0x14) = 0x15501003;
	}
	if(data == 0xa8f7){
		REG32(QSPI_BASE_ADDR + 0x14) = 0x15501002;
	}
	wait_device_not_busy();
}

void qspi_enter_xip(void)
{
	REG32(QSPI_BASE_ADDR) = 0x801c0081;// disable xip mode
}
