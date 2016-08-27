#pragma once


static inline u8	io_inb(
		u16	port)
{
	u8	data;
	__asm__ ("inb	%%dx, %%al" :
#ifdef	_TCC
			"=a" (data)
			: "d" (port));
#else
			"=al" (data)
			: "dx" (port));
#endif
	return	data;
}


static inline void	io_outb(
		u8	data,
		u16	port)
{
	__asm__ ("outb	%%al, %%dx" ::
#ifdef	_TCC
			"a" (data),
			"d" (port));
#else
			"al" (data),
			"dx" (port));
#endif
}


static inline void	io_outw(
		u16	data,
		u16	port)
{
	__asm__ ("outw	%%ax, %%dx" ::
			"ax" (data),
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


static inline u32	io_rdmsr(
		u32	addr)
{
	u32	res;
	__asm__ ("rdmsr"
#ifdef	_TCC
			: "=a" (res)
			: "c" (addr));
#else
			: "=eax" (res)
			: "ecx" (addr));
#endif
	return	res;
}


static inline void	io_wrmsr(
		u32	data,
		u32	addr)
{
	__asm__ ("wrmsr"
#ifdef	_TCC
		:: "a" (data), "c" (addr));
#else
		:: "eax" (data), "ecx" (addr));
#endif
}


