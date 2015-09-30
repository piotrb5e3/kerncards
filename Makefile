#Makefile for kerncards
HEADERS1 = kernel.h kwrite.h idt.h keyboard.h time.h random.h string.h
HEADERS2 = prompt.h card.h game.h
OBJS1 = kasm.o main.o kwrite.o idt.o keyboard.o time.o random.o string.o
OBJS2 = prompt.o card.o deck.o
HEADERS = $(HEADERS1) $(HEADERS2)
OBJS = $(OBJS1) $(OBJS2)
NASM = nasm
NASMFLAGS = -f elf32
CC = gcc
CCFLAGS = -m32 -Wall -c -fno-builtin
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
