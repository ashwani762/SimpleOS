/*
*  kernel.c
*/

#include "system.h"

void 
kmain( void )
{
	install_modules();
	cls();

	start_screen();

	while(1);
	
}