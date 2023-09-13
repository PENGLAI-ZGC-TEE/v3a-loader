.macro my_memory_copy, dst, src, size
	li a4, \dst
	li a5, \src
	li a3, \size
	li a2, 0 
copy:
	ld a6, 0(a5)
	sd a6, 0(a4)
	addi a2, a2, 8
	addi a4, a4, 8
	addi a5, a5, 8
	bltu a2, a3, copy 
.endm

.section ".text.boot"

.global _start
_start:
	li t0, 4096
	la sp, stack_top
	add sp, sp, t0
	
	li a3, 0
	la a4, wake
	sd a3, 0(a4)
	
	csrr a0, mhartid
	beqz a0, copy_and_run 

wait_for_copy_and_run:
	la a1, wake
	ld a4, 0(a1)
	beqz a4, wait_for_copy_and_run
	j no_copy_and_run

copy_and_run:
	jal print_info
	my_memory_copy 0x90000000, 0x80000000, 0x1000
	la a4, wake
	li a3, 1
	sd a3, 0(a4)

Loop:
	j Loop

no_copy_and_run:
	jal print_info

stack_top:
	.skip 4096
wake:
	.skip 8
