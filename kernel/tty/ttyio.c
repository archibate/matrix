#include	"../kernel.h"
#include	"ttyio.h"
#include	"../asf.h"


u16	*cur_p	= VRAM;


void	printstr(
		const char	*str,
		int	col)
{
	char	ch;
	col <<= 8;
	for (;;) {
		switch (ch = *str++) {
		case '\n':
			cur_p += TTY_XS;
			continue;
		case 0:
			return;
		case '\r':
			cur_p -= (cur_p - VRAM) % TTY_XS;
			continue;
		default:
			*cur_p++ = ch | col;
			continue;
		}
	}
}


