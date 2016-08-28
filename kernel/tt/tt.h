#pragma once


#define	TSS0_PAD	0x00002E00
#define	IOMAX_MAX	0
#define	TASKS_PAD	0x00002000
#define	TASK_MAX	64

#define	TASK_EXIST	1
#define	TASK_BLOCKED	2

#define	SEND		1
#define	RECV		2
#define	BOTH		3

#define	MSG_GOT_WAIT_BLOCKED	4

#define	TT_DAE		2

#define	TT_SCNR_exit		1
#define	TT_SCNR_fork		2

struct	tss {		/* 我们的内核只使用了一个 TSS */
	r_t	back, esp0, ss0, esp1, ss1, esp2, ss2,
		cr3, eip, efl, eax, ecx, edx, ebx, esp,
		ebp, esi, edi, es, cs, ss, ds, fs, gs, ldtr;
	u16	trag_sym;
	u16	iomap_ofs;
#if	IOMAP_MAX != 0
	u8	iomap[IOMAP_MAX];
#endif
	u8	iomap_end;
} __attribute__ ((packed));

typedef	u16	pid_t;

struct	sfr {	/* isr_route 压入的寄存器 */
	r_t	gs, fs, es, ds, edi, esi, ebp, new_esp,
		ebx, edx, ecx, eax, isr_nr, err_code,
		eip, cs, efl, esp, ss;
} __attribute__ ((packed));

struct	msg_got {
	u8	*buf;
	size_t	buf_size;
	pid_t	sender;
	u8	status;
};

struct	task {
	struct sfr	sfr;
	//struct task	*cld_lst;
	//struct task	*next_cld;
	//struct task	*parent;
	u16	flags;
	u16	status;
	struct msg_got	msg_got;
	char	name[16];
};

#define	task_exist(task)	((task)->status & TASK_EXIST)
#define	task_empty(task)	(!task_exist(task))
#define	task_enable(task)	((task)->status |= TASK_EXIST)
#define	task_disable(task)	((task)->status &= ~TASK_EXIST)
#define	task_blocked(task)	((task)->status & TASK_BLOCKED)
#define	task_unblocked(task)	(!task_blocked(task))
#define	block_task(task)	((task)->status |= TASK_BLOCKED)
#define	unblock_task(task)	((task)->status &= ~TASK_BLOCKED)
#define	save_stack_frame(sfrx)	(task_ready->sfr = *(sfrx))


void	init_tt();
void	tt_daemon();
struct task	*schedule();
struct task	*init_task(
		struct task	*task,
		r_t	cs,
		r_t	eip,
		r_t	ds,
		r_t	esp);
int	tt_sends(
		pid_t	pid,
		const void	*buf,
		size_t	*psize);
pid_t	tt_recvs(
		pid_t	pid,
		void	*buf,
		size_t	*psize);
void	print_task_table();
void	tt_iret();	/* 定义在 tt.s 中 */
void	task_idle_main();


