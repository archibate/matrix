#pragma once


static inline u8	io_inb(
		u16	port)
{
#ifdef	__GNUC__
	u8	data;
#endif
	__asm__ ("inb	%%dx, %%al" :
#ifdef	__GNUC__
			"=al" (data)
#endif
			: "dx" (port));
#ifdef	__GNUC__
	return	data;
#endif
}


static inline void	io_outb(
		u8	data,
		u16	port)
{
	__asm__ ("outb	%%al, %%dx" ::
			"al" (data),
			"dx" (port));
}


static inline void	io_hlt()
{
	__asm__ ("hlt");
}


static inline void	io_sti()
{
	__asm__ ("sti");
}


static inline void	io_cli()
{
	__asm__ ("cli");
}


