.text
.globl	tt_iret
.extern	task_ready	# in tt.c


tt_iret:
	movl	task_ready, %esp

	popl	%gs
	popl	%fs
	popl	%es
	popl	%ds
	popal

	addl	$8, %esp	# skip isr_nr & err_code in struct sfr
	iretl
