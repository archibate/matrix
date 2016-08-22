#include	"../kernel.h"
#include	"desc.h"
#include	"pic.h"
#include	"../asf.h"


void	init(void)	/* we were called from start.s */
{
	(* (u16 *) 0x000B8000) = 0x0C03;

	init_gdt();
	init_idt();
	init_pic();
	io_sti();

	for (;;) {
		io_hlt();
	}
}


