OUTPUT_ARCH("riscv")
ENTRY(_start)
SECTIONS
{	
	. = 0x8c800000,
	/*. = 0x80000000,*/
	.text.boot : { *(.text.boot) }
	.text : { *(.text) }
	.rodata : { *(.rodata) }
	.data : { *(.data) }
	.bss : { *(.bss) }
}
