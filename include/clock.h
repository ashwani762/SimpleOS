#ifndef __CLOCK_H__
#define __CLOCK_H__

#include "isr.h"
#include "irq.h"

void clock_handler();
void clock_install(); 
unsigned int getHours();
unsigned int getMins();
unsigned int getSec();

#endif