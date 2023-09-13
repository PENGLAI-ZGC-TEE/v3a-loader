.macro memory_copy, dst, src, size
	li a4, \dst
	li a5, \src
	li a3, \size
	li a2, 0 
1:
	ld a6, 0(a5)
	sd a6, 0(a4)
	addi a2, a2, 8
	addi a4, a4, 8
	addi a5, a5, 8
	bltu a2, a3, 1b 
.endm

.section ".text.boot"
  
.global _start
_start:
	// set sp to 0xFF000000 (point to the end of ddr) as a temporary stack 
	li t0, 4096
	li sp, 0xFF000000
	add sp, sp, t0

	jal uart_init

	// init 0x39001008 (use to notify other to run)
	li a3, 0
	la a4, 0x39001008
	sd a3, 0(a4)
	
	// only boot hart do copy_and_run
	csrr a0, mhartid
	beqz a0, copy_and_run

	// other harts spin here until 0x39001008 is set to 1 by boot hart
wait_for_copy_and_run:
	la a1, 0x39001008
	ld a4, 0(a1)
	beqz a4, wait_for_copy_and_run
	j no_copy_and_run

copy_and_run:
	jal print_hart_info

	li a0, 0x10300000
	li a1, 0x80000000
	li a2, 0x844000
	jal print_downloading_info

	// copy uefi from qspi flash to ddr
	// the src corresponds to the pack script (pack.sh)
	memory_copy 0x80000000, 0x10300000, 0x844000
	
	li a0, 0x13d00000
	li a1, 0x83a00000
	li a2, 0x3000
	jal print_downloading_info

	// copy dtb from qspi flash to ddr
	// the offset of dtb in uefi.fd is defined by FDF file in UEFI 
	memory_copy 0x83a00000, 0x13d00000, 0x3000

	// boot hart set 0x39001008 to 1 to notify other harts to continue to run
	la a4, 0x39001008
	li a3, 1
	sd a3, 0(a4)

	li a0, '#'
	jal uart_putc

	//boot hart jump to ddr (start of uefi)
	li t1, 0x80000000
	jr t1
Loop0:
	j Loop0

	// other harts jump to ddr (start of uefi)
no_copy_and_run:
	csrr a0, mhartid
	jal print_hart_info
	li t1, 0x80000000
	jr t1
Loop1:
	j Loop1
