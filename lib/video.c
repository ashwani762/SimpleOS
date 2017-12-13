#include "video.h"
#include "ioports.h"


//
// Constant
//-----------------------------------------------
#define start_video_mem 0xB8000
#define width   80
#define lines    25
//
// Structure to access directly to the video mem
//-----------------------------------------------
typedef struct {
    unsigned char c;
    unsigned char attr;
} __attribute__ ((packed)) video_mem[width*lines];

// Make the structure point to the good address
//-----------------------------------------------
static volatile video_mem *screen = (volatile video_mem *)start_video_mem;

// Global vars
//-----------------------------------------------

static short aff= BG_BLACK | WHITE;
static int cursor_x, cursor_y = 0;
char command[width*lines];

//
// CLS : Clear the screen
//-----------------------------------------------
void cls(){

	long i;
	
	for(i=0;i<width*lines;++i){
	    (*screen)[i].c=0;
	    (*screen)[i].attr=aff;
	}

	cursor_x = 0;
	cursor_y = 0;
	move_cursor();
}

//
// Move Cursor
//------------------------------------------------
static void move_cursor(){
	unsigned int cursorLocation = cursor_y * width + cursor_x;
	outb(0x3D4, 14);
	outb(0x3D5, cursorLocation >> 8);
	outb(0x3D4, 15);
	outb(0x3D5, cursorLocation);
}

//
// Scroll window
//----------------------------------------------
static void scroll(){
	if(cursor_y >= 25){
		int i;
		for(i = 0*width; i < 24 * 80; i++){
			(*screen)[i].c = (*screen)[i+80].c;
			(*screen)[i].attr = (*screen)[i+80].attr;
		}

		for(i = 24 * 80; i< 25 * 80; i++){
			(*screen)[i].c = ' ';
			(*screen)[i].attr = aff;
		}

		cursor_y = 24;
	}
}

//
// affchar : Display character at current position
//------------------------------------------------
void printchar(char c){
	unsigned int location;
	if(c == 0x08 && cursor_x){
		cursor_x--;
		location = (cursor_y * 80 + cursor_x);
		(*screen)[location].c = 0;
		(*screen)[location].attr = aff;
	}

	else if(c == 0x09){
		cursor_x = (cursor_x + 8) & ~(8 - 1);
	}

	else if(c == '\r'){
		cursor_x = 0;
	}

	else if(c == '\n'){
		cursor_x = 0;
		cursor_y++;
	}

	else if(c >= ' '){
		location = cursor_y * 80 + cursor_x;
		(*screen)[location].c = c;
		(*screen)[location].attr = aff;
		cursor_x++;
	}

	if(cursor_x >= 80){
		cursor_x = 0;
		cursor_y++;
	}

	scroll();

	move_cursor();

}


//
// Print
//------------------------------------------------
void print(char* str){
	int i = 0;
	while(str[i]){
		printchar(str[i++]);
	}
}
//
// iPrint
//------------------------------------------------
void iprint(int number){
	char str[256]; 
	int i=256;
	if(number == 0 ){
	   print("0");
	   return;
	}
	str[i--]=0;
	
	while(number > 0 ){
	  str[i--]='0'+(number%10);
	  number/=10;	   
	}
	print(str+i+1);
	return;
}
//
// Modify the current attributes
//------------------------------------------------
void chg_color(short color){
		aff=color;
}
//
// locate on the screen
//
void locate(int h, int w){
	cursor_x=h;
	cursor_y=w;
	move_cursor();
}

// Basic functions for memory manipulation
void *memcpy(void *dest, const void *src, int count)
{
    const char *sp = (const char *)src;
    char *dp = (char *)dest;
    for(; count != 0; count--) *dp++ = *sp++;
    return dest;
}
void *memset(void *dest, char val, int count)
{
    char *temp = (char *)dest;
    for( ; count != 0; count--) *temp++ = val;
    return dest;
}
unsigned short *memsetw(unsigned short *dest, unsigned short val, int count)
{
    unsigned short *temp = (unsigned short *)dest;
    for( ; count != 0; count--) *temp++ = val;
    return dest;
}

//
//Delayed text animation
//
void delay_text(char *string, int ticks){

}

int str_len(char *string){
	int i=0;
	while(string[i]!=0x0){
		if(string[i]=='\n'||string[i]=='\t')
			continue;
		i++;
	}

	return i;
}

void setbgcolor(short aff){
	long i;
	
	for(i=0;i<width*lines;++i){
	    (*screen)[i].c=0;
	    (*screen)[i].attr=aff;
	}
}
