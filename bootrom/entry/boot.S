
.section ".text.boot"
  
.global _start
_start:
        li      ra, 0             //li 指令对应addi
        li      sp, 0
        li      gp, 0
        li      tp, 0
        li      t0, 0
        li      t1, 0
        li      t2, 0
        li      s0, 0
        li      s1, 0
        li      a0, 0
        li      a1, 0
        li      a2, 0
        li      a3, 0
        li      a4, 0
        li      a5, 0
        li      a6, 0
        li      a7, 0
        li      s2, 0
        li      s3, 0
        li      s4, 0
        li      s5, 0
        li      s6, 0
        li      s7, 0
        li      s8, 0
        li      s9, 0
        li      s10, 0
        li      s11, 0
        li      t3, 0
        li      t4, 0
        li      t5, 0
        li      t6, 0
        li      t0, 0      //将1 加载到t0寄存器            
	// set sp to 0xFF000000 (point to the end of ddr) as a temporary stack 
	//li t0, 4096
	//li sp, 0xE0000000
	//add sp, sp, t0
        //disable irq
        //jal soc_cru
        jal gpio
        j .
        csrw mie, zero
        //set expeption handler
        la t0, sbi_exception_vector
        csrw mtvec, t0
        //set pmp
        li t0, 0
        csrw pmpaddr0, t0
        li t0, -1
        csrw pmpaddr1, t0
        li t0, 0x1f
        csrw pmpcfg0, t0
        //master core and slave core wait
        csrr t0, mhartid
        li t1, 0
        bne t0, t1, wait
	jal uart_init
        jal _main    
        j .        
     
.align 3
wait:	
       j .
.align 3
sbi_exception_vector:
        j . 
