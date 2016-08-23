#pragma once


#define	TSS0_PAD	0x00002200
#define	IOMAX_MAX	0


struct	tss {		/* our kernel use only one TSS */
	u_t	back, esp0, ss0, esp1, ss1, esp2, ss2,
		cr3, eip, efl, eax, ecx, edx, ebx, esp,
		ebp, esi, edi, es, cs, ss, ds, fs, gs, ldtr;
	u16	trag_sym;
	u16	iomap_ofs;
#if	IOMAP_MAX != 0
	u8	iomap[IOMAP_MAX];
#endif
	u8	iomap_end;
} __attribute__ ((packed));


void	init_tt();


