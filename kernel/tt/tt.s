.text
.globl	tt_iret
.globl	task_idle_main
.extern	task_ready	# 在 tt.c 中


tt_iret:
	movl	task_ready, %esp

	popl	%gs
	popl	%fs
	popl	%es
	popl	%ds
	popal

	addl	$8, %esp	# 跳过 isr_nr & err_code
	iretl

task_idle_main:
	#hlt
	jmp	task_idle_main

.code16

.globl	smi_handler

smi_handler:
	#.word	0xEA66
	#.long	0
	#.word	smi_go

smi_go:
	movw	%cs, %ax
	movw	%ax, %ds
	movw	%ax, %es
	movw	%ax, %ss
	movw	%ax, %fs
	movw	%ax, %gs
	movw	$0, %sp

	pushw	$0xB800
	popw	%gs
	movw	$0xFFFF, %gs:0
	jmp	.
	rsm
	
