#include	"kernel.h"


void	init(void)
{
	(* (u16 *) 0x000B8000) = 0x0C03;	/* Suprise!?! */
	for (;;) {
		__asm__ ("hlt");
	}
}


