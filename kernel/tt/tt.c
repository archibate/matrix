#include	"../kernel.h"
#include	"tt.h"
#include	"../mm/mm.h"
#include	"../init/desc.h"
#include	"../init/pic.h"
#include	"../lib/memory.h"
#include	"../tty/ttyio.h"


struct task	*task_ready;	/* 当前进程结构体指针 */
struct task	*tasks	= (struct task *) TASKS_PAD;


void	task_a_main();
void	task_b_main();
void	task_c_main();


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
	memset(&tasks[0], 0, sizeof(struct task));
	tasks[0].sfr.cs = USER_CODE_SEL;
	tasks[0].sfr.ds = tasks[0].sfr.ss
		= tasks[0].sfr.es = tasks[0].sfr.fs
		= tasks[0].sfr.gs = USER_DATA_SEL;
	tasks[0].sfr.esp = tasks[0].sfr.ebp
		= STACK_PAD;
	tasks[0].sfr.eip = (r_t) task_a_main;
	tasks[0].sfr.efl = 0x3202;
	task_enable(&tasks[0]);
	memset(&tasks[1], 0, sizeof(struct task));
	tasks[1].sfr.cs = USER_CODE_SEL;
	tasks[1].sfr.ds = tasks[1].sfr.ss
		= tasks[1].sfr.es = tasks[1].sfr.fs
		= tasks[1].sfr.gs = USER_DATA_SEL;
	tasks[1].sfr.esp = tasks[1].sfr.ebp
		= STACK_PAD;
	tasks[1].sfr.eip = (r_t) task_b_main;
	tasks[1].sfr.efl = 0x3202;
	task_enable(&tasks[1]);
	memset(&tasks[2], 0, sizeof(struct task));
	tasks[2].sfr.cs = USER_CODE_SEL;
	tasks[2].sfr.ds = tasks[2].sfr.ss
		= tasks[2].sfr.es = tasks[2].sfr.fs
		= tasks[2].sfr.gs = USER_DATA_SEL;
	tasks[2].sfr.esp = tasks[2].sfr.ebp
		= STACK_PAD;
	tasks[2].sfr.eip = (r_t) task_c_main;
	tasks[2].sfr.efl = 0x3202;
	task_enable(&tasks[2]);
	task_ready = &tasks[0];
	tt_iret();
}


struct task	*schedule()
{
	//printf("schedule called\r\n");
	struct task	*task = task_ready + 1;
	for (; task < tasks + TASK_MAX; ++task) {
		if (task_exist(task)) {
			return	task_ready = task;
		}
	}
	/*
	 * 已经遍历到了进程表底部，
	 * 从顶端重新搜索
	 */
	for (task = tasks; task <= task_ready; ++task) {
		if (task_exist(task)) {
			return	task_ready = task;
		}
	}
	printf("TT : FATAL ERROR : schedule : "
			"no task avliable in task table!\r\n");
	return	NULL;
}


void	task_a_main()
{
	for (;;) {
		//task_ready = &tasks[1];
		//VRAM[5] = 0x0C03;
		//VRAM[5] = 0x0B0D;
		//VRAM[5] = 0x0D0C;
		VRAM[7] = (0x0A << 8) + 'A';
		//printstr("task A running!\r\n", 0x07);
	}
}


void	task_b_main()
{
	for (;;) {
		//task_ready = &tasks[0];
		//VRAM[5] = 0x0C03;
		//VRAM[5] = 0x0B0D;
		//VRAM[5] = 0x0D0C;
		VRAM[7] = (0x0C << 8) + 'B';
		//printstr("task B running!\r\n", 0x07);
	}
}


void	task_c_main()
{
	for (;;) {
		//task_ready = &tasks[0];
		//VRAM[5] = 0x0C03;
		//VRAM[5] = 0x0B0D;
		//VRAM[5] = 0x0D0C;
		VRAM[7] = (0x0E << 8) + 'C';
		//printstr("task c running!\r\n", 0x07);
	}
}


