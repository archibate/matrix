#include	"../kernel.h"
#include	"tt.h"
#include	"../mm/mm.h"
#include	"../init/desc.h"
#include	"../init/pic.h"
#include	"../lib/memory.h"
#include	"../tty/ttyio.h"


struct task	*task_ready;
struct task	*tasks	= (struct task *) TASKS_PAD;


void	task_a_main();


void	init_tt()
{
	struct tss	*tss0	= (struct tss *) TSS0_PAD;
	memset(tss0, 0, sizeof(struct tss));
	tss0->ss0	= SYS_DATA_SEL;
	tss0->esp0	= STACK_PAD;
	tss0->iomap_ofs	= sizeof(struct tss);
	tss0->iomap_end	= 0xFF;
	__asm__ ("ltr	%%ax"
			:: "ax" (TSS_DESC_SEL));
	//__asm__ ("cli;hlt");
	
	//task_ready = &tasks[0];
	memset(task_ready, 0, sizeof(struct task));
	task_ready->sfr.cs = USER_CODE_SEL;
	task_ready->sfr.ds = task_ready->sfr.ss
		= task_ready->sfr.es = task_ready->sfr.fs
		= task_ready->sfr.gs = USER_DATA_SEL;
	task_ready->sfr.esp = task_ready->sfr.ebp
		= STACK_PAD;
	task_ready->sfr.eip = (r_t) task_a_main;
	task_ready->sfr.efl = 0x3202;
	tt_iret();
}


void	task_a_main()
{
	for (;;) {
		//VRAM[5] = 0x0C03;
		//VRAM[5] = 0x0B0D;
		//VRAM[5] = 0x0D0C;
		//printstr("task A running!\r\n", 0x07);
	}
}


