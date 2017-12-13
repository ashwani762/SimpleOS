#ifndef __VIDEO_H__
#define __VIDEO_H__

#include "ioports.h"
#include "timer.h"

#define KEYBOARD_DATA_PORT 0x60
#define KEYBOARD_STATUS_PORT 0x64
#define IDT_SIZE 256
#define INTERRUPT_GATE 0x8e
#define KERNEL_CODE_SEGMENT_OFFSET 0x08


//Colors
#define BLACK 		0
#define BLUE		1
#define GREEN		2
#define CYAN		3
#define RED			4
#define MAGENTA		5
#define BROWN		6
#define LIGHTGRAY	7
#define DARKGRAY	8
#define LIGHTBLUE	9
#define LIGHTGREEN	10
#define LIGHTCYAN	11
#define LIGHTRED	12
#define LIGHTMAGENTA 13
#define YELLOW		14
#define WHITE		15

//Background Colors
#define BG_BLACK 		(0<<4)
#define BG_BLUE			(1<<4)
#define BG_GREEN		(2<<4)
#define BG_CYAN			(3<<4)
#define BG_RED			(4<<4)
#define BG_MAGENTA		(5<<4)
#define BG_BROWN		(6<<4)
#define BG_LIGHTGRAY	(7<<4)
#define BG_DARKGRAY		(8<<4)
#define BG_LIGHTBLUE	(9<<4)
#define BG_LIGHTGREEN	(10<<4)
#define BG_LIGHTCYAN	(11<<4)
#define BG_LIGHTRED		(12<<4)
#define BG_LIGHTMAGENTA (13<<4)
#define BG_YELLOW		(14<<4)
#define BG_WHITE		(15<<4)

#define MAX_VIDPTR 80*25

extern void *memcpy(void *dest, const void *src, int count);
extern void *memset(void *dest, char val, int count);
extern unsigned short *memsetw(unsigned short *dest, unsigned short val, int count);

static void move_cursor();
static void scroll();

void cls();
void printchar(char c);
void chg_color(short color);
void print(char* str);
void iprint(int number);
void locate(int h, int w);
void delay_text(char *string, int ticks);
int str_len(char *string);
void setbgcolor(short aff);


#endif