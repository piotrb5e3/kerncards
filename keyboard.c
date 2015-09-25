/*
 * keyboard.c
 */

#include "kernel.h"
#include "idt.h"


//============Private constants:
#define KEYBOARD_DATA_PORT 0x60
#define KEYBOARD_STATUS_PORT 0x64
#define KEYBOARD_INTERRUPT_LINE_NUMBER 0x1


//============Private variables:
//Dummy callback function:
int dummy_clb(char c)
{
    return 0;
}

//Callback function
int (*clb)(char) = dummy_clb;

//Keyboard map:
unsigned char keyboard_map[128] =
{
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
    /* Backspace */
    '\t',
    /* Tab */
    'q', 'w', 'e', 'r',  't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
    /* Enter key */
    0,
    /* 29   - Control */
    'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`',   0,
    /* Left shift */
    '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/',   0,
    /* Right shift */
    '*',
    0,	/* Alt */
  ' ',	/* Space bar */
    0,	/* Caps lock */
    0,	/* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,	/* < ... F10 */
    0,	/* 69 - Num lock*/
    0,	/* Scroll Lock */
    0,	/* Home key */
    0,	/* Up Arrow */
    0,	/* Page Up */
  '-',
    0,	/* Left Arrow */
    0,
    0,	/* Right Arrow */
  '+',
    0,	/* 79 - End key*/
    0,	/* Down Arrow */
    0,	/* Page Down */
    0,	/* Insert Key */
    0,	/* Delete Key */
    0,   0,   0,
    0,	/* F11 Key */
    0,	/* F12 Key */
    0,	/* All other keys are undefined */
};

//============Private functions:
//
//== Handle keyboard interrupts
void keyboard_handler_main(void)
{
	unsigned char status;
	char keycode;

	status = read_port(KEYBOARD_STATUS_PORT);

	/* Lowest bit of status will be set if buffer is not empty */
	if (status & 0x01) {
		keycode = read_port(KEYBOARD_DATA_PORT);

		if(keycode >= 0){

                    //decode key
                    keycode = keyboard_map[keycode];
                    //call callback function
                    if(clb(keycode)!=0){
                        //TODO: panic!
                    }
                }
	}
        //Write EOI - signal end of interrupt
        write_port(0x20, 0x20);
}

//============Public interface functions:
void kbd_idt_init(struct IDT_entry *idt, unsigned short int selector,
        unsigned char type_attr)
{
    unsigned long keyboard_address;
    
    /*populate IDT entry*/
    keyboard_address = (unsigned long) keyboard_handler;
    idt[KEYBOARD_INTERRUPT_LINE_NUMBER].offset_lowerbits =
        keyboard_address & 0xffff;
    idt[KEYBOARD_INTERRUPT_LINE_NUMBER].selector = selector;
    idt[KEYBOARD_INTERRUPT_LINE_NUMBER].zero = 0;
    idt[KEYBOARD_INTERRUPT_LINE_NUMBER].type_attr = type_attr;
    idt[KEYBOARD_INTERRUPT_LINE_NUMBER].offset_higherbits =
        (keyboard_address & 0xffff0000) >> 16;
 }

void kbd_enable(void)
{
    //TODO: enable IRQ1 without disabling other IRQ's
    /* 0xFD is 11111101 - enables only IRQ1 (keyboard)*/
    write_port(0x21 , 0xFD);

}

void kbd_set_callback(int (*callback)(char))
{
    clb = callback;
}

