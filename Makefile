#Makefile for kerncards

all: kernel.i386

kernel.i386: kc.o kasm.o
	ld -m elf_i386 -T link.ld -o kernel.i386 kasm.o kc.o

kasm.o: kernel.asm
	nasm -f elf32 kernel.asm -o kasm.o

kc.o: kernel.c
	gcc -m32 -c kernel.c -o kc.o

clean:
	rm -f kernel kc.o kasm.o
