#Makefile for kerncards
HEADERS = kwrite.h

all: kernel.i386

kernel.i386: kc.o kasm.o kwrite.o $(HEADERS)
	ld -m elf_i386 -T link.ld -o kernel.i386 kasm.o kc.o kwrite.o

kasm.o: kernel.asm $(HEADERS)
	nasm -f elf32 kernel.asm -o kasm.o

kc.o: kernel.c $(HEADERS)
	gcc -m32 -c kernel.c -o kc.o

kwrite.o: kwrite.c $(HEADERS)
	gcc -m32 -c kwrite.c -o kwrite.o

clean:
	rm -f kernel kc.o kasm.o
