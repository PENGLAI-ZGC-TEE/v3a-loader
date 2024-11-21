
.section ".text.boot"
  
.global _start
_start:
	// set sp to 0xFF000000 (point to the end of ddr) as a temporary stack 
	//li t0, 4096
	//li sp, 0xE0000000
	//add sp, sp, t0
        //disable irq
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
