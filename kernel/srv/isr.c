#include	"../kernel.h"
#include	"isr.h"
#include	"../init/desc.h"
#include	"../init/pic.h"
#include	"../tty/ttyio.h"
#include	"../asf.h"


void	isr_int0x00()
{
	(* (u16 *) 0x000B8004) = 0x0303;
}


void	isr_int0x01()
{
	(* (u16 *) 0x000B8004) = 0x0303;
}


void	isr_int0x02()
{
	(* (u16 *) 0x000B8004) = 0x0303;
}


void	isr_int0x03()
{
	(* (u16 *) 0x000B8004) = 0x0303;
}


void	isr_int0x04()
{
	(* (u16 *) 0x000B8004) = 0x0303;
}


void	isr_int0x05()
{
	(* (u16 *) 0x000B8004) = 0x0303;
}


void	isr_int0x06()
{
	(* (u16 *) 0x000B8004) = 0x0303;
}


void	isr_int0x07()
{
	(* (u16 *) 0x000B8004) = 0x0303;
}


void	isr_int0x08()
{
	(* (u16 *) 0x000B8004) = 0x0303;
}


void	isr_int0x09()
{
	(* (u16 *) 0x000B8004) = 0x0303;
}


void	isr_int0x0a()
{
	(* (u16 *) 0x000B8004) = 0x0303;
}


void	isr_int0x0b()
{
	(* (u16 *) 0x000B8004) = 0x0303;
}


void	isr_int0x0c()
{
	(* (u16 *) 0x000B8004) = 0x0303;
}


void	isr_int0x0d()
{
	(* (u16 *) 0x000B8004) = 0x0C03;
	__asm__ ("cli;hlt");
}


void	isr_int0x0e()
{
	(* (u16 *) 0x000B8004) = 0x0303;
}


void	isr_int0x0f()
{
	(* (u16 *) 0x000B8004) = 0x0303;
}


void	isr_int0x10()
{
	(* (u16 *) 0x000B8004) = 0x0303;
}


void	isr_int0x11()
{
	(* (u16 *) 0x000B8004) = 0x0303;
}


void	isr_int0x12()
{
	(* (u16 *) 0x000B8004) = 0x0303;
}


void	isr_int0x13()
{
	(* (u16 *) 0x000B8004) = 0x0303;
}


void	isr_int0x14()
{
	(* (u16 *) 0x000B8004) = 0x0303;
}


void	isr_int0x15()
{
	(* (u16 *) 0x000B8004) = 0x0303;
}


void	isr_int0x16()
{
	(* (u16 *) 0x000B8004) = 0x0303;
}


void	isr_int0x17()
{
	(* (u16 *) 0x000B8004) = 0x0303;
}


void	isr_int0x18()
{
	(* (u16 *) 0x000B8004) = 0x0303;
}


void	isr_int0x19()
{
	(* (u16 *) 0x000B8004) = 0x0303;
}


void	isr_int0x1a()
{
	(* (u16 *) 0x000B8004) = 0x0303;
}


void	isr_int0x1b()
{
	(* (u16 *) 0x000B8004) = 0x0303;
}


void	isr_int0x1c()
{
	(* (u16 *) 0x000B8004) = 0x0303;
}


void	isr_int0x1d()
{
	(* (u16 *) 0x000B8004) = 0x0303;
}


void	isr_int0x1e()
{
	(* (u16 *) 0x000B8004) = 0x0303;
}


void	isr_int0x1f()
{
	(* (u16 *) 0x000B8004) = 0x0303;
}


void	isr_int0x20()	/* timer IRQ */
{
	(* (u16 *) 0x000B8004) = 0x0303;
	//static u16	*next_heart = (u16 *) 0x000B8006;
	//*next_heart++ = 0x0303;
	(* (u16 *) 0x000B8000)++;
	//printstr("timer IRQ called\r\n", 0x07);
	io_outb(0x60, 0x20);
}


void	isr_int0x21()	/* keyboard IRQ */
{
	(* (u16 *) 0x000B8004) = 0x0303;
	printstr("keyboard IRQ called\r\n", 0x07);
	io_outb(0x20, 0x20);
}


void	isr_int0x22()
{
	(* (u16 *) 0x000B8004) = 0x0303;
}


void	isr_int0x23()
{
	(* (u16 *) 0x000B8004) = 0x0303;
}


void	isr_int0x24()
{
	(* (u16 *) 0x000B8004) = 0x0303;
}


void	isr_int0x25()
{
	(* (u16 *) 0x000B8004) = 0x0303;
}


void	isr_int0x26()
{
	(* (u16 *) 0x000B8004) = 0x0303;
}


void	isr_int0x27()
{
	(* (u16 *) 0x000B8004) = 0x0303;
}


void	isr_int0x28()
{
	(* (u16 *) 0x000B8004) = 0x0303;
}


void	isr_int0x29()
{
	(* (u16 *) 0x000B8004) = 0x0303;
}


void	isr_int0x2a()
{
	(* (u16 *) 0x000B8004) = 0x0303;
}


void	isr_int0x2b()
{
	(* (u16 *) 0x000B8004) = 0x0303;
}


void	isr_int0x2c()
{
	(* (u16 *) 0x000B8004) = 0x0303;
}


void	isr_int0x2d()
{
	(* (u16 *) 0x000B8004) = 0x0303;
}


void	isr_int0x2e()
{
	(* (u16 *) 0x000B8004) = 0x0303;
}


void	isr_int0x2f()
{
	(* (u16 *) 0x000B8004) = 0x0303;
}


void	isr_int0x30()
{
	(* (u16 *) 0x000B8004) = 0x0303;
	printstr("ISR 0x30 called\r\n", 0x07);
}


void	isr_int0x31()
{
	(* (u16 *) 0x000B8004) = 0x0303;
}


void	isr_int0x32()
{
	(* (u16 *) 0x000B8004) = 0x0303;
}


