#pragma once


#define	VRAM_PAD	0x000B8000	/* text mode VRAM here */
#define	VRAM		((u16 *) VRAM_PAD)
#define	TTY_XS		80		/* XSize and YSize */
#define	TTY_YS		25
#define	TTY_DEFCOL	0x07


void	printstr(
		const char	*str,
		int	col);
void	clean_screen();
void	scrollup_screen();


