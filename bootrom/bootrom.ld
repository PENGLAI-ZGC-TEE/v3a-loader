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
        
	.boot2bin :
        {
            . = ALIGN(16);
            *(.boot2bin);
        }
	.fw_payload :
        {
            . = ALIGN(16);
            *(.fw_payload);
        }

}
