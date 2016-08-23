#include	"../kernel.h"
#include	"ttyio.h"
#include	"../lib/memory.h"
#include	"../asf.h"


static inline u16	get_cur_sub();
static inline void	set_cur_sub(
		u16		cur);


void	printstr(
		const char	*str,
		int	col)
{
	u16	*cur_p	= VRAM + get_cur_sub();
	char	ch;
	col <<= 8;
	for (;;) {
		switch (ch = *str++) {
		case '\n':
			if (cur_p >= VRAM + TTY_XS * (TTY_YS - 1)) {
				scrollup_screen();
				continue;
			}
			cur_p += TTY_XS;
			continue;
		case 0:
			set_cur_sub(cur_p - VRAM);
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


void	clean_screen()
{
	u16	*p = VRAM;
	set_cur_sub(0);
	/*while (p < VRAM + TTY_XS * TTY_YS)
		*p++ = 0x0700;*/
	memset_word(VRAM, 0x0700, TTY_XS * TTY_YS);
}


void	scrollup_screen()
{
	u16	*p = VRAM - 1;
	/*while (++p < VRAM + TTY_XS * (TTY_YS - 1)) {
		*p = p[TTY_XS];
	}*/
	memcpy_word(VRAM, VRAM + TTY_XS, TTY_XS * (TTY_YS - 1));
	memset_word(VRAM + TTY_XS * (TTY_YS - 1), 0x0700, TTY_XS);
}


static inline u16	get_cur_sub()
{
#ifndef	__SINC__
	u16	ret;
#endif
	__asm__ (	"movw	$0x03D4, %%dx\n"
			"movb	$0x0E, %%al\n"
			"outb	%%al, %%dx\n"
			"incw	%%dx\n"	
			"inb	%%dx, %%al\n"
			"movb	%%al, %%ah\n"
			"decw	%%dx\n"	
			"movb	$0x0F, %%al\n"
			"outb	%%al, %%dx\n"
			"incw	%%dx\n"	
			"inb	%%dx, %%al\n"
			: "=ax" (ret) : );
#ifndef	__SINC__
	return	ret;
#endif
}


static inline void	set_cur_sub(
		u16		cur)
{
	__asm__ (	"movw	$0x03D4, %%dx\n"
			"movb	$0x0F, %%al\n"
			"outb	%%al, %%dx\n"
			"incw	%%dx\n"
			"movw	%%cx, %%ax\n"
			"outb	%%al, %%dx\n"
			"decw	%%dx\n"
			"movb	$0x0E, %%al\n"
			"outb	%%al, %%dx\n"
			"incw	%%dx\n"
			"movb	%%ah, %%al\n"
			"outb	%%al, %%dx\n"
			:: "cx" (cur));

	//cur_pos = cur;
}


