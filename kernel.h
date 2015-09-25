/*
 * kernel.h
 * declares functions found in kernel.asm
 */
#ifndef __KERNEL_H__
#define __KERNEL_H__

//Callback function for keyboard interrupts
void keyboard_handler(void);

//Read from given port
char read_port(unsigned short port);

//Write supplied byte to given port
void write_port(unsigned short port, unsigned char data);

//Load IDT 
void load_idt(unsigned long *idt_ptr);

#endif /* __KERNEL_H__ */
