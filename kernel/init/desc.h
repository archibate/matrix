#pragma once


#define	GDT_PAD		0x00001800
#define	IDT_PAD		0x00001000
#define	GDT_PAPV	((u64 *) GDT_PAD)
#define	IDT_PAPV	((u64 *) IDT_PAD)
#define	GDT_MAX		64
#define	IDT_MAX		256
#define	ISR_MAX		0x33

#define	ZERO_DESC_SEL	0x0000
#define	SYS_CODE_SEL	0x0008
#define	SYS_DATA_SEL	0x0010
#define	TSS_DESC_SEL	0x0020

#define	DA_32		0x8000
#define	DA_G		0x4000
#define	DA_DPL0		0x00
#define	DA_DPL1		0x20
#define	DA_DPL2		0x40
#define	DA_DPL3		0x60
#define	DA_DR		0x90
#define	DA_DRW		0x92
#define	DA_DRWA		0x93
#define	DA_C		0x98
#define	DA_CR		0x9A
#define	DA_CCO		0x9C
#define	DA_CCOR		0x9E
#define	DA_LDT		0x82
#define	DA_CG		0x8C
#define	DA_IG		0x8E
#define	DA_TG		0x8F
#define	DA_TSS		0x89
#define	DA_LDT		0x82


void	init_gdt();
void	init_idt();
void	set_seg_desc(		/* Segment Descriptor */
		u64	*dscr,
		u_t	base,
		u_t	limit,
		u16	attr);	/* How about to set them inline? */
void	set_gate_desc(		/* 386 Gate Descriptor */
		u64	*dscr,
		u16	select,
		u_t	offset,
		u8	dcount,
		u16	attr);
extern u_t	isr_entry_tab[ISR_MAX << 1];
extern u_t	isr_tab[ISR_MAX << 1];	/* they are defined in isr.s */
void	isr_default(void);


