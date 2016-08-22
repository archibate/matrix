.text
.global	isr_route

isr_route:
	pushw	%ds
	pushw	%es
	pushw	%fs
	pushw	%gs
	pushal
	
	popal
	popw	%gs
	popw	%fs
	popw	%es
	popw	%ds
	iretl

