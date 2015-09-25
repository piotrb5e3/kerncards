#Makefile for kerncards
HEADERS = kernel.h kwrite.h idt.h keyboard.h time.h random.h string.h card.h game.h
OBJS = kasm.o main.o kwrite.o idt.o keyboard.o time.o random.o string.o
NASM = nasm
NASMFLAGS = -f elf32
CC = gcc
CCFLAGS = -O3 -m32 -Wall -c
LD = ld
LDFLAGS = -m elf_i386 -T
LDSCRIPT = link.ld
EXE = kernel.i386

all: $(EXE)

$(EXE): $(OBJS) $(HEADERS)
	$(LD) $(LDFLAGS) $(LDSCRIPT) -o $@ $(OBJS)

kasm.o: kernel.asm
	$(NASM) $(NASMFLAGS) $< -o $@

#Generic C rule
%.o: %.c $(HEADERS)
	$(CC) $(CCFLAGS) $< -o $@

clean:
	rm -f $(OBJS) $(EXE)
