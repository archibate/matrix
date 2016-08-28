#include	"../kernel.h"
#include	"tt.h"
#include	"../mm/mm.h"
#include	"../init/desc.h"
#include	"../init/pic.h"
#include	"../lib/memory.h"
#include	"../tty/ttyio.h"
#include	"../fs/fs.h"
#include	"../lib/string.h"


struct task	*task_ready;	/* 当前进程结构体指针 */
struct task	*tasks	= (struct task *) TASKS_PAD;


void	task_a_main();
void	task_b_main();
void	task_c_main();


u8	unused_stack_1[4096];
u8	task_idle_stack[4096];
u8	task_a_stack[4096];
u8	task_b_stack[4096];
u8	task_c_stack[4096];
u8	tt_daemon_stack[8192];
u8	fs_daemon_stack[8192];


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
	/*memset(&tasks[0], 0, sizeof(struct task));
	tasks[0].sfr.cs = USER_CODE_SEL;
	tasks[0].sfr.ds = tasks[0].sfr.ss
		= tasks[0].sfr.es = tasks[0].sfr.fs
		= tasks[0].sfr.gs = USER_DATA_SEL;
	tasks[0].sfr.esp = tasks[0].sfr.ebp
		= (r_t) task_a_stack;
	tasks[0].sfr.eip = (r_t) task_a_main;
	tasks[0].sfr.efl = 0x3202;
	task_enable(&tasks[0]);*//*9d69*/
	init_task(&tasks[0], USER_CODE_SEL, (r_t) task_idle_main,
			USER_DATA_SEL, (r_t) task_idle_stack +
			sizeof(task_idle_stack));
	init_task(&tasks[8], USER_CODE_SEL, (r_t) task_a_main,
			USER_DATA_SEL, (r_t) task_a_stack +
			sizeof(task_a_stack));
	init_task(&tasks[9], USER_CODE_SEL, (r_t) task_b_main,
			USER_DATA_SEL, (r_t) task_b_stack +
			sizeof(task_b_stack));
	init_task(&tasks[10], USER_CODE_SEL, (r_t) task_c_main,
			USER_DATA_SEL, (r_t) task_c_stack +
			sizeof(task_c_stack));
	/*memset(&tasks[1], 0, sizeof(struct task));
	tasks[1].sfr.cs = USER_CODE_SEL;
	tasks[1].sfr.ds = tasks[1].sfr.ss
		= tasks[1].sfr.es = tasks[1].sfr.fs
		= tasks[1].sfr.gs = USER_DATA_SEL;
	tasks[1].sfr.esp = tasks[1].sfr.ebp
		= (r_t) task_b_stack;
	tasks[1].sfr.eip = (r_t) task_b_main;
	tasks[1].sfr.efl = 0x3202;
	task_enable(&tasks[1]);
	memset(&tasks[2], 0, sizeof(struct task));
	tasks[2].sfr.cs = USER_CODE_SEL;
	tasks[2].sfr.ds = tasks[2].sfr.ss
		= tasks[2].sfr.es = tasks[2].sfr.fs
		= tasks[2].sfr.gs = USER_DATA_SEL;
	tasks[2].sfr.esp = tasks[2].sfr.ebp
		= (r_t) task_c_stack;
	tasks[2].sfr.eip = (r_t) task_c_main;
	tasks[2].sfr.efl = 0x3202;
	task_enable(&tasks[2]);
	memset(&tasks[1], 0, sizeof(struct task));
	tasks[1].sfr.cs = USER_CODE_SEL;
	tasks[1].sfr.ds = tasks[1].sfr.ss
		= tasks[1].sfr.es = tasks[1].sfr.fs
		= tasks[1].sfr.gs = USER_DATA_SEL;
	tasks[1].sfr.esp = tasks[1].sfr.ebp
		= (r_t) task_b_stack;
	tasks[1].sfr.eip = (r_t) task_b_main;
	tasks[1].sfr.efl = 0x3202;
	task_enable(&tasks[1]);
	memset(&tasks[2], 0, sizeof(struct task));
	tasks[2].sfr.cs = USER_CODE_SEL;
	tasks[2].sfr.ds = tasks[2].sfr.ss
		= tasks[2].sfr.es = tasks[2].sfr.fs
		= tasks[2].sfr.gs = USER_DATA_SEL;
	tasks[2].sfr.esp = tasks[2].sfr.ebp
		= (r_t) task_c_stack;
	tasks[2].sfr.eip = (r_t) task_c_main;
	tasks[2].sfr.efl = 0x3202;
	task_enable(&tasks[2]);
	memset(&tasks[1], 0, sizeof(struct task));
	tasks[1].sfr.cs = USER_CODE_SEL;
	tasks[1].sfr.ds = tasks[1].sfr.ss
		= tasks[1].sfr.es = tasks[1].sfr.fs
		= tasks[1].sfr.gs = USER_DATA_SEL;
	tasks[1].sfr.esp = tasks[1].sfr.ebp
		= (r_t) task_b_stack;
	tasks[1].sfr.eip = (r_t) task_b_main;
	tasks[1].sfr.efl = 0x3202;
	task_enable(&tasks[1]);
	memset(&tasks[2], 0, sizeof(struct task));
	tasks[2].sfr.cs = USER_CODE_SEL;
	tasks[2].sfr.ds = tasks[2].sfr.ss
		= tasks[2].sfr.es = tasks[2].sfr.fs
		= tasks[2].sfr.gs = USER_DATA_SEL;
	tasks[2].sfr.esp = tasks[2].sfr.ebp
		= (r_t) task_c_stack;
	tasks[2].sfr.eip = (r_t) task_c_main;
	tasks[2].sfr.efl = 0x3202;
	task_enable(&tasks[2]);*/
	init_task(&tasks[TT_DAE], USER_CODE_SEL, (r_t) tt_daemon,
			USER_DATA_SEL, (r_t) tt_daemon_stack +
			sizeof(tt_daemon_stack));
	init_task(&tasks[FS_DAE], USER_CODE_SEL, (r_t) fs_daemon,
			USER_DATA_SEL, (r_t) fs_daemon_stack +
			sizeof(fs_daemon_stack));
	task_ready = tasks;	/* task_idle */
	//printk("task_b_stack = %p", (r_t) task_b_stack);
	//panic("hi");
	//
}


void	tt_daemon()
{
	pid_t	sender;
	static int	recv_buf[8];
	static size_t	recv_size;
	strcpy(task_ready->name, "TT");

	for (;;) {
		memset(recv_buf, 0, recv_size = sizeof(recv_buf));
		sender = tt_recvs(0, recv_buf, &recv_size);

		switch (recv_buf[0]) {
		case TT_SCNR_exit:
			task_disable(tasks + sender);
			continue;
		case TT_SCNR_fork:
			continue;
		default:
			printk("System Call Error : %d is not an index of TT SysCall",
					recv_buf[0]);
			continue;
		}
	}
}


struct task	*schedule()
{
	//printk("tt/schedule called");
	//print_task_table();
	struct task	*task = task_ready + 1;
	for (; task < tasks + TASK_MAX; ++task) {
		if (task_exist(task) && task_unblocked(task)) {
			//printk("tt/schedule : schedule to PID = %d", task - tasks);
			return	task_ready = task;		/* 寻找下一个存在的进程 */
		}
	} /*
	   * 已经遍历到了进程表底部，
	   * 从顶端重新搜索
	   */
	for (task = tasks; task <= task_ready; ++task) {
		if (task_exist(task) && task_unblocked(task)) {
			//printk("tt/schedule : schedule to PID = %d", task - tasks);
			return	task_ready = task;
		}
	}
	printk("tt/schedule : No task avilable in task table!");
	//panic("tt/schedule : No task avilable in task table!");
	return	NULL;
}


struct task	*init_task(
		struct task	*task,
		r_t	cs,
		r_t	eip,
		r_t	ds,
		r_t	esp)
{
	memset(task, 0, sizeof(struct task));
	task->sfr.cs = cs;
	task->sfr.ds = task->sfr.ss
		= task->sfr.es = task->sfr.fs
		= task->sfr.gs = ds;
	task->sfr.esp = task->sfr.ebp
		= esp;
	task->sfr.eip = eip;
	task->sfr.efl = 0x3202;
	task_enable(task);
	return	task;
}


/*void	save_sfr(
		const struct sfr	*sfr)
{
	task_ready->sfr = *sfr;
}*/


int	tt_sends(
		pid_t	pid,
		const void	*buf,
		size_t	*psize)
{
	int	erres;
	__asm__ (	"movl	$1, %%eax\n"
			"int	$0x30\n" :
			"=a" (erres),
			"=c" (*psize) :
			"b" (buf),
			"c" (*psize),
			"d" (pid));
	return	erres;
}


pid_t	tt_recvs(
		pid_t	pid,
		void	*buf,
		size_t	*psize)
{
	pid_t	sender;
	__asm__ (	"movl	$2, %%eax\n"
			"int	$0x30\n" :
			"=a" (sender),
			"=c" (*psize) :
			"b" (buf),
			"c" (*psize),
			"d" (pid));
	return	sender;
}


void	print_task_table()
{
	struct task	*task;
	/*printk("Task Table :");
	printk(" PID  STAT   CS:EIP        SS:ESP     ");*/
	for (task = tasks; task < tasks + TASK_MAX; ++task) {
		if (task_exist(task)) {
			printk("%5d %c%c%c- %4p:%p %4p:%p", task - tasks,
					task_exist(task) ? 'e' : '-',
					task == task_ready ? 'r' : '-',
					task_blocked(task) ? 'b' : '-',
					task->sfr.cs, task->sfr.eip,
					task->sfr.ss, task->sfr.esp);
		}
	}
}


static u16	*next_abc_p	= VRAM + 10;


void	task_a_main()
{
	static char	send_buf[64] = "Secretly love you... \x03\0";
	size_t	sended_size = sizeof(send_buf);
	strcpy(task_ready->name, "task_a");
	printk("I'm sending message to Task B : %s", send_buf);
	while (tt_sends(9, send_buf, &sended_size));	/* Task B */
	//panic("DDSDSAFsfadsasrDFSf3452345sdfsf");
	printk("sended size is %d, Oh no, she do not has enough buf...",
			sended_size);
	static int	scargs[8] = {0};
	static size_t	scasize = sizeof(scargs[8]);
	/*scargs[0] = FS_SCNR_dev_open;
	scasize = 4;
	while (tt_sends(FS_DAE, &scargs, &scasize));
	scargs[0] = TT_SCNR_exit;
	scasize = 4;
	while (tt_sends(TT_DAE, &scargs, &scasize));*/
	for (;;) {
		//task_ready = &tasks[1];
		//VRAM[5] = 0x0C03;
		//VRAM[5] = 0x0B0D;
		//VRAM[5] = 0x0D0C;
		VRAM[7] = (0x0A << 8) + 'A';
		/* sendrecv(1, SEND, 1); */
		//*next_abc_p++ = (0x0A << 8) + 'A';
		if (next_abc_p >= VRAM + TTY_XS * TTY_YS) {
			next_abc_p = VRAM;
			//clean_screen();
		}
		for (int times = 0; times < 1000; times++);
		//delay_down(100);
		//printstr("task A running!\r\n", 0x07);
	}
}


void	task_b_main()
{
	static char	recv_buf[8 + 1] = {0};
	pid_t	sender_pid;
	size_t	recved_size = sizeof(recv_buf) - 1;
	strcpy(task_ready->name, "task_b");
	sender_pid = tt_recvs(0, recv_buf, &recved_size);
	recv_buf[recved_size] = 0;
	printk("I recived message from PID %d : %s", sender_pid, recv_buf);
	printk("?? Sorry, what do you mean?");
	printk("recived size is %d", recved_size);
	for (;;) {
		//task_ready = &tasks[0];
		//VRAM[5] = 0x0C03;
		//VRAM[5] = 0x0B0D;
		//VRAM[5] = 0x0D0C;
		VRAM[7] = (0x0C << 8) + 'B';
		//VRAM[8] = (0x0C << 8) + 'B';
		//*next_abc_p++ = (0x0C << 8) + 'B';
		if (next_abc_p >= VRAM + TTY_XS * TTY_YS) {
			next_abc_p = VRAM;
			//clean_screen();
		}
		for (int times = 0; times < 1000; times++);
		/*for (int times = 0; times < 10000000; times++);*/
		/*clean_screen();*/
		/*memset_word(VRAM, 0x110A, TTY_XS * TTY_YS);*/
		/*printstr("\r\n  An ERROR occured durning the initialize stage.\r\n", 0x17);*/
		/*printstr("\r\n  If you have seen this before, please contact me at ", 0x17);*/
		/*printstr("4008-517-517\r\n", 0x1F);*/
		/*printstr("\r\n\r\n  Unsolved exception occoured from ", 0x17);*/
		/*printstr("C:\\Windows\\System32\\Macdownload_Ieat.exe\r\n", 0x1F);*/
		/*printstr("  (non-debug mode reported)\r\n\r\n", 0x17);*/
		/*printstr("  DWORD Dump ERROR :\r\n\r\n", 0x17);*/
		/*printstr("        #0043BE12  #55621F34\r\n"*/
			/*"        #24E4D625  #A07B5647\r\n        #4C58D390  #8F4C5E26"*/
			/*"\r\n\r\n\r\n\r\n\r\n", 0x1F);*/
		/*panic("BLUE OF THE DEATH");*/
		/*//delay_down(100);*/
		/*//printstr("task B running!\r\n", 0x07);*/
	}
}


void	task_c_main()
{
	strcpy(task_ready->name, "task_c");
	for (;;) {
		//task_ready = &tasks[0];
		//VRAM[5] = 0x0C03;
		//VRAM[5] = 0x0B0D;
		//VRAM[5] = 0x0D0C;
		VRAM[7] = (0x0E << 8) + 'C';
		//*next_abc_p++ = (0x0E << 8) + 'C';
		if (next_abc_p >= VRAM + TTY_XS * TTY_YS) {
			next_abc_p = VRAM;
			//clean_screen();
		}
		for (int times = 0; times < 1000; times++);
		//delay_down(100);
		//printstr("task C running!\r\n", 0x07);
	}
}


