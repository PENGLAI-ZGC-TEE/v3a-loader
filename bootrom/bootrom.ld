OUTPUT_ARCH("riscv")
ENTRY(_start)
SECTIONS
{	
	. = 0x2200000,
	/*. = 0x80000000,*/
	.text.boot : { *(.text.boot); }
	.text : { *(.text); }
	.rodata : { *(.rodata); }
	.bss : { *(.bss); }
	.data : { *(.data); }
        
       	. = ALIGN(8);
	.boot2bin :
        {
                *(.boot2bin);
                . = ALIGN(8);
        }

}
