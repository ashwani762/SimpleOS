#ifndef __SYSTEM_H__
#define __SYSTEM_H__

#include "video.h"
#include "gdt.h"
#include "irq.h"
#include "idt.h"
#include "isr.h"
#include "timer.h"
#include "kb.h"
#include "clock.h"

void install_modules();
void start_screen();

#endif