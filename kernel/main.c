/*
*  kernel.c
*/

#include "system.h"

void 
kmain( void )
{
	install_modules();
	cls();

	locate(40-str_len(start_string)/2, 12);
	chg_color(GREEN);
	delay_text(start_string, 2);

	timer_wait(3);
	cls();

	locate(0,0);
	chg_color(WHITE);
	delay_text(welcome,2);

	locate(0,23);
	for(i=0;i<80;i++){
		print("-");
	}

	locate(0,24);

	while(1);
	
}