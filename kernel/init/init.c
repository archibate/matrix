#include	"../kernel.h"
#include	"desc.h"
#include	"pic.h"
#include	"../tt/tt.h"
#include	"../tty/ttyio.h"
#include	"../mm/mm.h"
#include	"../asf.h"


void	init(void)	/* init() were called from start.s */
{
	//(* (u16 *) 0x000B8000) = 0x0C03;

	init_gdt();
	init_idt();
	init_pic();
	init_pit();
	init_tt();
	io_sti();
	clean_screen();
	printstr("Hello, TelType!\r\nI'm MATRIX!\r\n", 0x07);

	__asm__ ("int	$0x30");

	for (;;) {
		io_hlt();
	}
}


