/*
 * idt.c
 */

#include "idt.h"
#include "keyboard.h"
#include "kernel.h"

//====Constants:
#define IDT_SIZE 256
#define INTERRUPT_GATE 0x8e
#define KERNEL_CODE_SEGMENT_OFFSET 0x08
#define IDT_OFFSET 0x20
#define LINES_PER_PIC 8
#define PIC1_COMMAND 0x20
#define PIC1_DATA 0x21
#define PIC2_COMMAND 0xA0
#define PIC2_DATA 0xA1



struct IDT_entry IDT[IDT_SIZE];


void idt_init(void)
{
	unsigned long idt_address;
	unsigned long idt_ptr[2];

	/* populate IDT entry of keyboard's interrupt */
        kbd_idt_init(&(IDT[IDT_OFFSET]), KERNEL_CODE_SEGMENT_OFFSET,
                INTERRUPT_GATE);

	/* ICW1 - begin initialization */
	write_port(PIC1_COMMAND , 0x11);
	write_port(PIC2_COMMAND , 0x11);

	/* ICW2 - remap offset address of IDT */
	/*
	* In x86 protected mode, we have to remap the PICs beyond 0x20 because
	* Intel have designated the first 32 interrupts as "reserved"
        * for cpu exceptions
	*/
	write_port(PIC1_DATA , IDT_OFFSET);
	write_port(PIC2_DATA , IDT_OFFSET + LINES_PER_PIC);

	/* ICW3 - setup cascading */
        //0x00 - no cascading
	write_port(PIC1_DATA , 0x00);
	write_port(PIC2_DATA , 0x00);

	/* ICW4 - environment info */
	write_port(PIC1_DATA , 0x01);
	write_port(PIC2_DATA , 0x01);

	/* Initialization finished */

	/* mask interrupts */
	write_port(PIC1_DATA , 0xff);
	write_port(PIC2_DATA , 0xff);

	/* fill the IDT descriptor */
	idt_address = (unsigned long)IDT ;
	idt_ptr[0] = (sizeof (struct IDT_entry) * IDT_SIZE)
            + ((idt_address & 0xffff) << 16);
	idt_ptr[1] = idt_address >> 16 ;

        //Flush idt
	load_idt(idt_ptr);
}

