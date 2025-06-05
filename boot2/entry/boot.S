
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
	li sp, 0xE0000000
        //master core and slave core wait
        csrr t0, mhartid
        li t1, 0
        bne t0, t1, wait
        
        csrw mie, zero
        //set expeption handler
        la t0, sbi_exception_vector
        csrw mtvec, t0
        jal _main    
        j .        
     
.align 3
wait:	
       wfi
       csrr t0, mip
       andi t0, t0, 1 << 3
       beqz t0, wait
       jal boot2_core1
.align 3
sbi_exception_vector:
        j . 
