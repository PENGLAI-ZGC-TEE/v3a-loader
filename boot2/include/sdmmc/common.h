#ifndef _COMMON_H_
#define _COMMON_H_

#include "print.h"
#include "uart.h"
typedef unsigned int  uint32_t;

//void delay(unsigned int loops);
int wait_sv(int id);
void sync_sv(int id, int msg);
int polling(unsigned int addr, unsigned int data, unsigned int msk);
void fence();
uint32_t get_mhart_id();
void start_core1();
void start_core0();
void stop_core1();
void stop_core0();

#define set_bit1(in,pos) (in)=(in|(1<<pos))
#define set_bit0(in,pos) (in)=(in&(~(1<<pos)))

#define GPU_DDR_BASE 0x10000000//1000000~2ffffff
//#define SOFT_RST_TEST
//#define CLK_GATE_TEST
//#define NET_SIM
/*
#define REG_ADDR_TYPE (volatile unsigned int*)
#define REG_WRITE(addr, value)  (*((volatile unsigned int*)(addr))) = (value)
#define REG_READ(addr)  (*((volatile unsigned int*)(addr)))
#define MEM_WRITE(addr, value)  (*((volatile unsigned long long*)(addr))) = (value)
#define MEM_READ(addr)  (*((volatile unsigned long long*)(addr)))
#define BYTE_WRITE(addr, value)  (*((volatile unsigned char*)(addr))) = (value)
#define BYTE_READ(addr)  (*((volatile unsigned char*)(addr)))
*/
//tangdan
#define REG_ADDR_TYPE (volatile unsigned int*)
#define REG_WRITE(addr, value)  (*((volatile unsigned int*)(((unsigned long long)addr)))) = (value)
#define REG_READ(addr)  (*((volatile unsigned int*)(((unsigned long long)addr))))
#define MEM_WRITE(addr, value)  (*((volatile unsigned long long*)(((unsigned long long)addr)))) = (value)
#define MEM_READ(addr)  (*((volatile unsigned long long*)(((unsigned long long)addr))))
#define BYTE_WRITE(addr, value)  (*((volatile unsigned char*)(((unsigned long long)addr)))) = (value)
#define BYTE_READ(addr)  (*((volatile unsigned char*)(((unsigned long long)addr))))

#define MEM_WRITE32(addr, value)  (*((volatile unsigned int*)(((unsigned long long)addr)))) = (value)
#define MEM_READ32(addr)  (*((volatile unsigned int*)(((unsigned long long)addr))))

#endif

#define KMH
