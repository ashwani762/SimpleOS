#ifndef _IOPORTS_H_
#define _IOPORTS_H_

unsigned char inb(unsigned short port);
void outb(unsigned short port, unsigned char val);

#endif