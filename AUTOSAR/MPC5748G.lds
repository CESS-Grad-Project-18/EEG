OUTPUT_FORMAT("elf32-powerpc")
OUTPUT_ARCH(powerpc:common)

ENTRY(main)

MEMORY
{
  flash (rx)  : ORIGIN = 0x01000000, LENGTH = 256K
  /* ram(rwx) : ORIGIN = 0x40000000, LENGTH = 768K */
  ram0(rwx) : ORIGIN = 0x40000000, LENGTH = 8K
  ram1(rwx) : ORIGIN = 0x40002000, LENGTH = 56K
  ram2(rwx) : ORIGIN = 0x40010000, LENGTH = 64K
  /* ram3(rwx) : ORIGIN = 0x40020000, LENGTH = 128K
  ram4(rwx) : ORIGIN = 0x40040000, LENGTH = 256K
  ram5(rwx) : ORIGIN = 0x40080000, LENGTH = 256K */
  stack0    : ORIGIN = 0x400BE800, LENGTH = 2K
  stack1    : ORIGIN = 0x400BF000, LENGTH = 2K
  stack2    : ORIGIN = 0x400BF800, LENGTH = 2K
  regspace  : ORIGIN = 0xC0000000, LENGTH = 0x40000000 //?
}

/* SECTIONS {
	. = 0x01000000;
	.start : { crt0.o(*) }
	.text : { *(.text) }
	.rodata : { *(.rodata .rodata.*)}
	.data : { *(.data) }

	__bss_start = .;
	.bss : { *(.bss) }
	__bss_end = .;

	. = ALIGN(0x40);
	.stack : {
		. += 0x8000;
		_stack_top = .;
	}
} */
 
SECTIONS{
     . = 0x01000000;
     .text : { *(.text) }
     .rodata : { *(.rodata .rodata.*)}
     .data : { *(.data) }
     .bss : { *(.bss) }
}
