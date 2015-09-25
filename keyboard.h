/*
 * keyboard.h
 */

#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__
#include "idt.h"

//Setup keyboard IDT entry
//*idt is the pointer to the beginning of offset IDT
//In most cases it should be &(idt[0x20])
void kbd_idt_init(struct IDT_entry *idt, unsigned short int selector,
        unsigned char type_attr);
//Enable keyboard interrupts
void kbd_enable(void);

//Setup callback function fo on_key_press
//Given callback function should follow this syntax:
////Return 0 on ok, <0 on not ok, c - character on the key that was pressed
//int foo(char c)
//{
// //code
//}
void kbd_set_callback(int (*callback)(char));

#endif /* __KEYBOARD_H__ */
