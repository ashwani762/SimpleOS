#include "system.h"

void install_modules(){
	gdt_install();
    idt_install();
    isrs_install();
    irq_install();
    timer_install();
    keyboard_install();

    __asm__ __volatile__ ("sti");
}

void start_screen(){
	
}