#ifndef __TIMER_H__
#define __TIMER_H__

#include "isr.h"
#include "irq.h"
#include "clock.h"

void timer_handler(struct regs *r);
void timer_install(); 
void timer_wait(int ticks);

#endif