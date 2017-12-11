OBJ = .obj
SRC = ./kernel
SRC_ASM = ./asm
SRC_LIB = ./lib
INCLUDE = ./include

#
# set up all compilers for working
#----------------------------------------
CC = gcc
AS = nasm
LD = ld

#
# Compilation flags
#----------------------------------------
OPT_C = -m32 -O -Wall -nostdlib -nostartfiles -nodefaultlibs -Wimplicit-function-declaration
OPT_ASM = -s -f elf32 -o

#
# Link option
#----------------------------------------
OPT_LD = -T link.ld -m elf_i386

#
# Main Targets
#----------------------------------------
all: ${OBJ} kernel.bin

build-iso: kernel.bin
	cp -rf kernel.bin isofiles/boot/kernel.bin
	grub-mkrescue -o os.iso isofiles

run-iso:
	qemu-system-i386 -cdrom os.iso

run:
	qemu-system-i386 -kernel kernel.bin

clean:
	rm -rf .obj/*
	rm -rf kernel.bin
	rm -rf isofiles/boot/kernel/bin
	rm -rf os.iso

${OBJ}:
	mkdir .obj

#
# Compilation directives
#----------------------------------------

kernel.bin:		${OBJ}/start.o \
				${OBJ}/main.o \
				${OBJ}/ioports.o \
				${OBJ}/video.o \
				${OBJ}/gdt.o \
				${OBJ}/idt.o \
				${OBJ}/isr.o \
				${OBJ}/irq.o \
				${OBJ}/kb.o \
				${OBJ}/clock.o \
				${OBJ}/system.o \
				${OBJ}/timer.o 
	${LD} ${OPT_LD} -o kernel.bin ${OBJ}/start.o \
		${OBJ}/ioports.o \
		${OBJ}/video.o \
		${OBJ}/gdt.o \
		${OBJ}/idt.o \
		${OBJ}/isr.o \
		${OBJ}/irq.o \
		${OBJ}/timer.o \
		${OBJ}/kb.o \
		${OBJ}/clock.o \
		${OBJ}/system.o \
		${OBJ}/main.o


#
# ---------------------------------------
${OBJ}/start.o: ${SRC_ASM}/start.asm
	${AS} ${OPT_ASM} ${OBJ}/start.o ${SRC_ASM}/start.asm

#
#----------------------------------------
${OBJ}/ioports.o: ${SRC_LIB}/ioports.c \
	$(INCLUDE)/ioports.h
	${CC} ${OPT_C} -c -o ${OBJ}/ioports.o -I${INCLUDE} ${SRC_LIB}/ioports.c

#
#----------------------------------------
${OBJ}/gdt.o: ${SRC_LIB}/gdt.c \
	$(INCLUDE)/gdt.h
	${CC} ${OPT_C} -c -o ${OBJ}/gdt.o -I${INCLUDE} ${SRC_LIB}/gdt.c

#
#----------------------------------------
${OBJ}/idt.o: ${SRC_LIB}/idt.c \
	$(INCLUDE)/idt.h
	${CC} ${OPT_C} -c -o ${OBJ}/idt.o -I${INCLUDE} ${SRC_LIB}/idt.c

#
#----------------------------------------
${OBJ}/irq.o: ${SRC_LIB}/irq.c \
	$(INCLUDE)/irq.h
	${CC} ${OPT_C} -c -o ${OBJ}/irq.o -I${INCLUDE} ${SRC_LIB}/irq.c
#
#----------------------------------------
${OBJ}/isr.o: ${SRC_LIB}/isr.c \
	$(INCLUDE)/isr.h
	${CC} ${OPT_C} -c -o ${OBJ}/isr.o -I${INCLUDE} ${SRC_LIB}/isr.c


#
#----------------------------------------
${OBJ}/video.o: ${SRC_LIB}/video.c \
	$(INCLUDE)/video.h
	${CC} ${OPT_C} -c -o ${OBJ}/video.o -I${INCLUDE} ${SRC_LIB}/video.c

#
#----------------------------------------
${OBJ}/kb.o: ${SRC_LIB}/kb.c \
	$(INCLUDE)/kb.h
	${CC} ${OPT_C} -c -o ${OBJ}/kb.o -I${INCLUDE} ${SRC_LIB}/kb.c

#
#----------------------------------------
${OBJ}/timer.o: ${SRC_LIB}/timer.c \
	$(INCLUDE)/timer.h
	${CC} ${OPT_C} -c -o ${OBJ}/timer.o -I${INCLUDE} ${SRC_LIB}/timer.c

#
#----------------------------------------
${OBJ}/clock.o: ${SRC_LIB}/clock.c \
	$(INCLUDE)/clock.h
	${CC} ${OPT_C} -c -o ${OBJ}/clock.o -I${INCLUDE} ${SRC_LIB}/clock.c

#
#----------------------------------------
${OBJ}/system.o: ${SRC_LIB}/system.c \
	$(INCLUDE)/system.h
	${CC} ${OPT_C} -c -o ${OBJ}/system.o -I${INCLUDE} ${SRC_LIB}/system.c


#
#----------------------------------------
${OBJ}/main.o: ${SRC}/main.c
	${CC} ${OPT_C} -c -o ${OBJ}/main.o -I${INCLUDE} ${SRC}/main.c
