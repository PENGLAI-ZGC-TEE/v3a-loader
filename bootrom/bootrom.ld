OUTPUT_ARCH("riscv")
ENTRY(_start)
SECTIONS
{	
	. = 0x10000000,
	.text.boot : { *(.text.boot) }
	.text : { *(.text) }
	.data : { *(.data) }
}
