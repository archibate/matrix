#include	"../kernel.h"
#include	"pic.h"
#include	"desc.h"
#include	"../asf.h"


void	init_pic()
{
	io_outb(0x11, 0x20);
	io_outb(0x11, 0xA0);
	io_outb(0x20, 0x21);
	io_outb(0x28, 0xA1);
	io_outb(0x04, 0x21);
	io_outb(0x02, 0xA1);
	io_outb(0x01, 0x21);
	io_outb(0x01, 0xA1);
	io_outb(0xFF, 0x21);
	io_outb(0xF8, 0xA1);
}


