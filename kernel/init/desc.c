#include	"../kernel.h"
#include	"desc.h"
#include	"../tt/tt.h"
#include	"../mm/mm.h"


#ifndef	_TCC
struct	{
	u16	limit;
	r_t	addr;
} __attribute__ ((packed)) __gdtr_val = {
	GDT_MAX * 8 - 1, GDT_PAD
};
struct	{
	u16	limit;
	r_t	addr;
} __attribute__ ((packed)) __idtr_val = {
	IDT_MAX * 8 - 1, IDT_PAD
};
#else
u64	__gdtr_val = (GDT_MAX * 8 - 1) | (GDT_PAD << 16);
u64	__idtr_val = (IDT_MAX * 8 - 1) | (IDT_PAD << 16);
#endif


void	init_gdt()
{
	set_seg_desc(GDT_PAPV + (ZERO_DESC_SEL >> 3),
		0, 0, 0);
	set_seg_desc(GDT_PAPV + (SYS_CODE_SEL >> 3),
		0x00000000, 0xFFFFFF, DA_C + DA_32 + DA_G + DA_DPL0);
	set_seg_desc(GDT_PAPV + (SYS_DATA_SEL >> 3),
		0x00000000, 0xFFFFFF, DA_DRW + DA_32 + DA_G + DA_DPL0);
	set_seg_desc(GDT_PAPV + (USER_CODE_SEL >> 3),
		0x00000000, 0xFFFFFF, DA_C + DA_32 + DA_G + DA_DPL3);
	set_seg_desc(GDT_PAPV + (USER_DATA_SEL >> 3),
		0x00000000, 0xFFFFFF, DA_DRW + DA_32 + DA_G + DA_DPL3);
	set_seg_desc(GDT_PAPV + (TSS_DESC_SEL >> 3),
		TSS0_PAD, sizeof(struct tss), DA_TSS);

	//__asm__ ("lgdt	%0" :: "m" (__gdtr_val));
	__asm__ ("lgdt	__gdtr_val");
	/* %cs, %ds, etc. will be reloaded until move_to_user_mode */
}


void	init_idt()
{
	int	i;
	for (i = 0; i < 0x30; i++) {
		set_gate_desc(IDT_PAPV + i, SYS_CODE_SEL,
				isr_entry_tab[i],
				0, DA_IG + DA_DPL0);
	}
	for (i = 0; i < 0x33; i++) {
		set_gate_desc(IDT_PAPV + i, SYS_CODE_SEL,
				isr_entry_tab[i],
				0, DA_IG + DA_DPL3);
	}
	for (; i < 256; i++) {
		set_gate_desc(IDT_PAPV + i, SYS_CODE_SEL,
				(r_t) isr_default,
				0, DA_IG + DA_DPL0);
	}

	__asm__ ("lidt	%0" :: "m" (__idtr_val));
}


void	isr_default(void)
{
	(* (u16 *) 0x000B8002) = 0x0C03;
}


void	set_seg_desc(
		u64	*dscr,
		r_t	base,
		r_t	limit,
		u16	attr)
{
	*dscr	= ((u64) (limit & 0x0FFFF)
		| ((u64) (base & 0x00FFFFFF) << 16)
		| ((u64) (attr & 0xF0FF) << 40)
		| ((u64) (base & 0xFF000000) << 32));
}


void	set_gate_desc(
		u64	*dscr,
		u16	select,
		r_t	offset,
		u8	dcount,
		u16	attr)
{
	*dscr	= ((u64) (offset & 0x0000FFFF)
		| ((u64) select << 16)
		| ((u64) (dcount & 0x1F) << 24)
		| ((u64) (attr) << 40)
		| ((u64) (offset & 0xFFFF0000) << 32));
}


