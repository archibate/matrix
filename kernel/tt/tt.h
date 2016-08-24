#pragma once


#define	TSS0_PAD	0x00002E80
#define	IOMAX_MAX	0
#define	TASKS_PAD	0x00002000
#define	TASK_MAX	64

#define	TASK_EXIST	1

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

struct	sfr {	/* isr_route 压入的寄存器 */
	r_t	gs, fs, es, ds, edi, esi, ebp, new_esp,
		ebx, edx, ecx, eax, isr_nr, err_code,
		eip, cs, efl, esp, ss;
} __attribute__ ((packed));

struct	task {
	struct sfr	sfr;
	u16	flags;
	u16	status;
};

#define	task_exist(task)	((task)->status & TASK_EXIST)
#define	task_enable(task)	((task)->status |= TASK_EXIST)


void	init_tt();
struct task	*schedule();
void	tt_iret();	/* 定义在 tt.s 中 */


