#include	"../kernel.h"
#include	"tt.h"
#include	"../mm/mm.h"
#include	"../init/desc.h"
#include	"../init/pic.h"
#include	"../lib/memory.h"


struct tss	*tss0	= (struct tss *) TSS0_PAD;


void	init_tt()
{
	memset(tss0, 0, sizeof(struct tss));
	tss0->ss0	= SYS_DATA_SEL;
	tss0->esp0	= STACK_PAD;
	tss0->iomap_ofs	= sizeof(struct tss);
	tss0->iomap_end	= 0xFF;
	__asm__ ("cli;hlt");
	__asm__ ("ltr	%%ax"
			:: "ax" (TSS_DESC_SEL));
}


