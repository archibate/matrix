#include	"../kernel.h"
#include	"isr.h"
#include	"../init/desc.h"
#include	"../init/pic.h"
#include	"../tt/tt.h"
#include	"../tty/ttyio.h"
#include	"../asf.h"
#include	"../tt/tt.h"
#include	"../lib/memory.h"


void	isr_int0x00()
{
	printk("INT 00 : Divide Error (#DE)");
}


void	isr_int0x01(
		struct sfr	sfr)
{
	clean_screen();
	printk("INT 01 : Debug Exception (#DB)");
	printk("Registers :");
	printk("EAX = %p  ECX = %p", sfr.eax, sfr.ecx);
	printk("EDX = %p  EBX = %p", sfr.edx, sfr.ebx);
	printk("ESI = %p  EDI = %p", sfr.esi, sfr.edi);
	printk("ESP = %p  EBP = %p", sfr.esp, sfr.ebp);
	printk("EFL = %p  EIP = %p", sfr.efl, sfr.eip);
	printk("CS  = %4p      SS  = %4p", sfr.cs, sfr.ss);
	printk("DS  = %4p      ES  = %4p", sfr.ds, sfr.es);
	printk("FS  = %4p      GS  = %4p", sfr.fs, sfr.gs);
	/*if (sfr.esp < sfr.ebp) {
		printk("Stack : length %d (%d element)",
				sfr.ebp - sfr.esp,
				(sfr.ebp - sfr.esp) >> 2);
		int	leaed_esp, leaed_ebp;
		__asm__ (	"pushl	%%fs\n"
				"movw	%%ax, %%fs\n"
				"leal	%%gs:(%%esi), %%edi\n"
				"popl	%%fs\n"
				: "=D" (leaed_esp)
				: "ax" (sfr.ss),
				"S" (sfr.esp));
		leaed_ebp = leaed_esp + sfr.ebp - sfr.esp;
		for (; leaed_esp < leaed_ebp;
				leaed_ebp -= 4) {
			printk("%p|%p|", sfr.ebp + leaed_esp - leaed_ebp,
					* (r_t *) leaed_ebp);
		}
	}*/
	panic("");
	sfr.efl |= (1 << 16);
}


void	isr_int0x02()
{
	printk("INT 02 : Not-Maskable Interrupt (NMI)");
}


void	isr_int0x03()
{
	printk("INT 03 : Break Point (#BP)");
}


void	isr_int0x04()
{
	printk("INT 04 : Overflow (#OF)");
}


void	isr_int0x05()
{
	printk("INT 05 : Bound Check (#BR)");
}


void	isr_int0x06()
{
	printk("INT 06 : Invalid Opcode (#UD)");
}


void	isr_int0x07()
{
	printk("INT 07 : Coprocessor Not Avalid (#NM)");
}


void	isr_int0x08()
{
	printk("INT 08 : Double Fault (#DF)");
}


void	isr_int0x09()
{
}


void	isr_int0x0a()
{
	printk("INT 0B : Invalid TSS (#TS)");
}


void	isr_int0x0b()
{
	printk("INT 0B : Senment Not Present (#NP)");
}


void	isr_int0x0c()
{
	printk("INT 0C : Stack Exception (#SS)");
}


void	isr_int0x0d(
		struct sfr	sfr)
{
	printk("INT 0D : Gernal Protect Excaption (#GP) from %4p:%p",
			sfr.cs, sfr.eip);
	//printk("GPE happened at %4p:%p");
	panic("Maybe someapp wanna hurt me @o@!");
	__asm__ ("cli;hlt");
}


void	isr_int0x0e()
{
	printk("INT 0E : Page Fault (#PF)");
}


void	isr_int0x0f()
{
	printk("INT 0F : Reserved ISR index");
}


void	isr_int0x10()
{
	printk("INT 10 : Corrpcessor Error (#MF)");
}


void	isr_int0x11()
{
	printk("INT 11 : Align Check (#AC)");
}


void	isr_int0x12()
{
	printk("INT 12 : Machine Check (#MC)");
}


void	isr_int0x13()
{
	printk("INT 13 : SIMD Float Exception (#XF)");
}


void	isr_int0x14()
{
}


void	isr_int0x15()
{
}


void	isr_int0x16()
{
}


void	isr_int0x17()
{
}


void	isr_int0x18()
{
}


void	isr_int0x19()
{
}


void	isr_int0x1a()
{
}


void	isr_int0x1b()
{
}


void	isr_int0x1c()
{
}


void	isr_int0x1d()
{
}


void	isr_int0x1e()
{
}


void	isr_int0x1f()
{
}


void	isr_int0x20(	/* timer IRQ */
		struct sfr	sfr)
{
	//static u16	*next_heart = (u16 *) 0x000B8006;
	//*next_heart++ = 0x0303;
	/*(* (u16 *) 0x000B8000)++;*/
	//printf("timer IRQ called\r\n");
	save_sfr(&sfr);		/*
				 * 保存 task_ready 进程的栈帧，
				 * 以便下次 tt_iret()
				 */
	schedule();	/* schedule() 会将 task_ready 设为下一个进程 */
	io_outb(0x60, 0x20);
	tt_iret();
}


void	isr_int0x21()	/* keyboard IRQ */
{
	printf("keyboard IRQ called\r\n");
	io_outb(0x20, 0x20);
}


void	isr_int0x22()
{
}


void	isr_int0x23()
{
}


void	isr_int0x24()
{
}


void	isr_int0x25()
{
}


void	isr_int0x26()
{
}


void	isr_int0x27()
{
}


void	isr_int0x28()
{
}


void	isr_int0x29()
{
}


void	isr_int0x2a()
{
}


void	isr_int0x2b()
{
}


void	isr_int0x2c()
{
}


void	isr_int0x2d()
{
}


void	isr_int0x2e()
{
}


void	isr_int0x2f()
{
}


void	isr_int0x30(
		struct sfr	sfr)
{
	//printk("INT 30 : System Call");
	extern struct task	*task_ready;
	extern struct task	*tasks;
	switch (sfr.eax) {
	case 1:	/* SEND */
		if (!sfr.ecx)
			break;
		//if (task_blocked(&tasks[sfr.edx])) {
#define	maxof(a, b)	((a) > (b) ? (a) : (b))
#define	minof(a, b)	((a) < (b) ? (a) : (b))
			if (task_ready == &tasks[sfr.edx]) {
				break;
			}
			if (tasks[sfr.edx].msg_got.buf == NULL)	{	/* target task not waiting for recv */
				sfr.eax = -1;
				break;
			}
			size_t	copy_size = minof(sfr.ecx, tasks[sfr.edx].msg_got.buf_size);
			memcpy(tasks[sfr.edx].msg_got.buf, (u8 *) sfr.ebx, copy_size);	/***[#COE!pageman] */
			tasks[sfr.edx].msg_got.sender = task_ready - tasks;
			//if (task_blocked(&tasks[sfr.edx])) {
				unblock_task(&tasks[sfr.edx]);
			//}
			tasks[sfr.edx].sfr.eax = task_ready - tasks;	/* tell reciver the PID of sender */
			sfr.ecx = tasks[sfr.edx].sfr.ecx = copy_size;	/*
									 * tell both reciver and sender
									 * the real copyed size
									 */
			tasks[sfr.edx].msg_got.buf = NULL;
			sfr.eax = 0;
			/*if (task_unblocked(&tasks[sfr.ebx]))
				printk("Unblocked task!!!");*/
		//}
		break;
	case 2:	/* RECV */
		if (!sfr.ecx)
			break;
		save_sfr(&sfr);
		block_task(task_ready);
		task_ready->msg_got.buf = (u8 *) sfr.ebx;
		task_ready->msg_got.buf_size = sfr.ecx;
		/*if (task_blocked(task_ready))
			printk("Blocked task!!!");*/
		schedule();
		tt_iret();
		break;
	case 3:
		break;
		/* sendrecv(MM_PID, SEND, MM_SR_ALLOC) */
	}
}


void	isr_int0x31()
{
}


void	isr_int0x32()
{
}


