#include	"../kernel.h"
#include	"pg.h"
#include	"../mm/mm.h"
#include	"../init/desc.h"
#include	"../tty/ttyio.h"


#define	set_pt(pt, pg, attr) \
	(* (u32 *) (pt) = (u32) (pg) | (u32) (attr))


void	init_pg()
{
	u32	*l2pt;
	u32	*l1pt;
	u32	pg;
	for (l2pt = L2PT_PAPV, l1pt = L1PT0_PAPV;
			l2pt < L2PT_PAPV + L1PT_MAX;
			++l2pt, l1pt += 0x1000) {
		set_pt(l2pt, l1pt, PA_P | PA_U | PA_W);
	}
	for (/*l2pt, l1pt*/;
			l2pt < L2PT_PAPV + 0x1000;
			++l2pt, l1pt += 0x1000) {
		set_pt(l2pt, l1pt, PA_U | PA_W);
	}
	for (l1pt = L1PT0_PAPV, pg = 0;
			l1pt < L1PT0_PAPV + L1PT_MAX;
			++l1pt, pg += 0x1000) {
		set_pt(l1pt, pg, PA_P | PA_U | PA_W);
	}
	//set_pt(l1pt + (L2PT_PAD >> 12), L2PT_PAD, PA_P | PA_W);
	__asm__ (	"movl	%%eax, %%cr3\n"	// a59a
			"movl	%%cr0, %%eax\n"
			"orl	$0x80000000, %%eax\n"
			"movl	%%eax, %%cr0\n"
			:: "a" (L2PT_PAD));
	//panic("YEAH!! PG-DONE!");
	/*remapgs(0x00200000, 0x00008000, 1);
	printk("Byte data 0x%02X at linear address 0x00200000",
			* (u8 *) 0x00200000);
	printk("Byte data 0x%02X at physical address 0x00008000",
			* (u8 *) 0x00008000);
	panic("YEAH!!");*/
}


void	remapg(
		u32	phy,
		u32	lin)
{
	u32	*p;
	p = & (((u32 *) (L2PT_PAPV [(phy & 0xFFC00000) >> 22]
		& 0xFFFFF000)) [(phy & 0x003FF000) >> 12]);
	*p &= 0xFFF;
	*p |= lin & 0xFFFFF000;
}


void	remapgs(
		u32	phy,
		u32	lin,
		u32	count)
{
	while (count--) {
		remapg(phy, lin);
		phy += 0x1000;
	}
}


