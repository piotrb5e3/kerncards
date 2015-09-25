/*
 * idt.h
 */

#ifndef __IDT_H__
#define __IDT_H__

//Structure for IDT entries
struct IDT_entry {
    unsigned short int offset_lowerbits;
    unsigned short int selector;
    unsigned char zero;
    unsigned char type_attr;
    unsigned short int offset_higherbits;
};

//Setup and flush IDT
void idt_init(void);

#endif /* __IDT_H__ */
