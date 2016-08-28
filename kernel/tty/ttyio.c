#include	"../kernel.h"
#include	"ttyio.h"
#include	"../lib/memory.h"
#include	"../tt/tt.h"
#include	"../lib/vsprintf.h"
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


int	printf(
	const char	*fmt,
	...)
{
	char	buf[1024];
	va_list	args = (va_list) ((r_t *) &fmt + 1);
	int	res = vsprintf(buf, fmt, args);	/* may overflow here */
	printstr(buf, 0x07);
	return	res;
}


int	printk(
	const char	*fmt,
	...)
{
	char	buf[1024];
	va_list	args = (va_list) ((r_t *) &fmt + 1);
	printstr("):", 0x07);
	extern struct task	*task_ready;
	int	res = vsprintf(buf + sprintf(buf, "[%8s]:", task_ready->name),
			fmt, args);	/* may overflow here */
	printstr(buf, 0x07);
	printstr("\r\n", 0x07);
	return	res;
}


void	panic(
		const char	*fmt,
		...)
{
	char	buf[1024];
	va_list	args = (va_list) ((r_t *) &fmt + 1);
	printstr("):", 0x07);
	extern struct task	*task_ready;
	printstr(">>>PANIC<<< : ", 0x0C);
	vsprintf(buf + sprintf(buf, "[%8s]:", task_ready->name),
			fmt, args);	/* may overflow here */
	printstr(buf, 0x0C);
	printstr("\r\n", 0x07);
	__asm__ ("cli;hlt");
}


void	clean_screen()
{
	//u16	*p = VRAM;
	set_cur_sub(0);
	/*while (p < VRAM + TTY_XS * TTY_YS)
		*p++ = 0x0700;*/
	memset_word(VRAM, 0x0700, TTY_XS * TTY_YS);
}


void	scrollup_screen()
{
	//u16	*p = VRAM - 1;
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
#ifdef	_TCC
			: "=a" (ret) : );
#else
			: "=ax" (ret) : );
#endif
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
#ifdef	_TCC
			:: "c" (cur));
#else
			:: "cx" (cur));
#endif

	//cur_pos = cur;
}


