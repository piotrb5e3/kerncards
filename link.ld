/*
 * link.ld
 *  parts of code by Arjun Sreedharan
 *  www.arjunsredharan.org
 */

OUTPUT_FORMAT(elf32-i386)
ENTRY(start)
SECTIONS
{
    . = 0x100000;
    .text : { *(.text) }
    .data : { *(.data) }
    .bss : { *(.bss) }

}
