#include	"../kernel.h"
#include	"desc.h"


void	init(void)	/* we were called from start.s */
{
	(* (u16 *) 0x000B8000) = 0x0C03;

	init_gdt();

	for (;;) {
		__asm__ ("hlt");
	}
}


