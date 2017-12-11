#include "clock.h"

volatile unsigned int hh, mm, ss;

void clock_handler(){
	volatile unsigned int timeH, timeM, timeS;

	outb(0x70,4);
	timeH = inb(0x71);
	hh = timeH - ((unsigned) timeH/16) * 6;

	outb(0x70,2);
	timeM = inb(0x71);
	mm = timeM - ((unsigned) timeM/16) * 6;

	outb(0x70,0);
	timeS = inb(0x71);
	ss = timeS - ((unsigned) timeS/16) * 6;
}

unsigned int getHours(){
	return hh;
}

unsigned int getMins(){
	return mm;
}

unsigned int getSec(){
	return ss;
}