.text
.code16
.global	_start

_start:		# we are loaded at 0x1000:0x0000, still real mode now
	jmp	rmode_start	# our boot loader do NOT set pmode

#ifdef	BITS64
.code32
pmode_start:			# now, we are in 0x8000:0x00010000 in pmode
	movw	$0x0010, %ax
	movw	%ax, %ds
	movw	%ax, %es
	movw	%ax, %ss
	movw	%ax, %fs
	movw	%ax, %gs

	movl	$0x001FFFF8, %esp	# reserve 8 byte above stack top
	movl	%esp, %ebp

	jmp	kernel_start
#else

.code64
lmode_start:
	movw	$0x0010, %ax
	movw	%ax, %ds
	movw	%ax, %es
	movw	%ax, %ss
	movw	%ax, %fs
	movw	%ax, %gs

	movq	$0x001FFFF8, %rsp
	movq	%rsp, %rbp

	movw	$0xFFFF, 0xB8000
	jmp	kernel_start
#endif

kernel_start:

	#movl	$0xC0000080, %ecx
	#rdmsr
	#movl	$0xB8000, %edi	# if we are succeed, we will see
	#movw	$0x0C03, %ax	# a red heart on Ln 1 Col 1
	#stosw


	call	init
	cli
	hlt

.code16
rmode_start:
	xorw	%ax, %ax
	movw	%ax, %ds	# let linker take care for it
	movw	%ax, %es
	movw	%ax, %ss
	movw	$stack_top, %sp
	movw	$msg_start, %si
	call	print_bios


#ifdef	BITS64
check_supp_lmode:	# use CPUID check if CPU support long-mode (64-bit)
	movl	$0x80000000, %eax
	cpuid
	cmp	$0x80000001, %eax
	jb	error
	movl	$0x80000001, %eax
	cpuid
	btl	$29, %edx
	jnc	error	# if not support long-mode, ERROR!
			# 64-bit kernel does not complied with 32-bit support
			# to use our kernel on i386, use command 'make ARCH=i386'
#endif

copy_gdt:
	pushw	$0x8000		# set GDT to 0x80000, templately,
	popw	%es		# we will set it later (in init)
	#movw	%cs, %ax
	#movw	%ax, %cx
	#shrw	$16, %ax	# high 4 bits let %cs:gdt0 out of 0xFFFF,
				# we need put it into 16~20 bit of GDT
				# physical address
	#movw	%ax, gdtr0 + 4	# high 16 bits of GDT 32-bit physical address
	#shlw	$4, %cx		# this compute low 16 bits of address
	#addw	$gdt0, %cx
	#movw	%ax, gdtr0 + 2	# so, wherever our kernel is loaded,
				# we can always get physical address of GDT
	#pushw	%cs
	pushw	$0
	popw	%ds
	xorw	%ax, %ax
	movw	%ax, %ss
	movw	%ax, %fs
	movw	%ax, %gs
	movw	%ax, %di
	movw	$gdt0, %si	# gdt0 is already added 0x8000 by linker
	movw	$gdt0_len >> 1, %cx	# gdt0_len should not be odd
	cld
	rep
	movsw
	xorw	%ax, %ax
	movw	%ax, %ds
	movw	%ax, %es

load_gdt:
	cli
	.byte	0x66		# 32-bit operand size prefix
	lgdt	%ds:gdtr0	# %ds is zero
				# while linking, gdtr0 will be set to
				# 0x80**, because we specified flag :
				# -Ttext 0x8000 in Makefile.

#ifdef	BITS64
enable_pae:
	movl	%cr4, %eax
	btsl	$5, %eax	# PAE
	movl	%eax, %cr4

init_lmode_pt:		# Will be reset in mm/pg.c
.equ	l4pt_ad,	0x00003000
.equ	l3pt_ad,	0x00004000
.equ	l2pt_ad,	0x00005000
.equ	l1pt_ad,	0x00050000
	pushl	$0
	popl	%ds
	movl	$l3pt_ad + 7, %ds:l4pt_ad
	movl	$0, %ds:l4pt_ad + 4
	movl	$l2pt_ad + 7, %ds:l3pt_ad
	movl	$0, %ds:l3pt_ad + 4
	movl	$l1pt_ad + 7, %ds:l2pt_ad
	movl	$0, %ds:l2pt_ad + 4
	movw	$l1pt_ad & 0xF, %di
	movl	$7, %ebx
	movl	$2048, %ecx
	pushl	$l1pt_ad >> 4
	popl	%es
next_page_desc:
	movl	%ebx, %eax
	#.byte	0x67		# 32-bit address prefix
	stosl	# stosl	%eax, %es:(%edi)
	xorl	%eax, %eax
	#.byte	0x67		# 32-bit address prefix
	stosl
	addl	$0x1000, %ebx
	loop	next_page_desc

load_cr3:
	movl	$l4pt_ad, %eax
	movl	%eax, %cr3

enable_lmode:
	movl	$0xC0000080, %ecx	# IA32_EFER
	rdmsr
	btsl	$8, %eax
	wrmsr
#endif

load_idt:
	.byte	0x66
	lidt	%ds:idtr0

	movb	$0xFF, %al
	outb	%al, $0xA1
	call	delay
	movb	$0xFF, %al
	outb	%al, $0x21

reset_math:
	movb	$0x00, %al
	outb	%al, $0xF0
	call	delay
	outb	%al, $0xF1
	call	delay

enable_a20:
	inb	$0x64, %al
	call	delay
	testb	$0x02, %al
	jnz	enable_a20
	movb	$0xDF, %al
	outb	%al, $0x64
	call	delay		# delay is required when doing I/O

load_cr0:
	movl	%cr0, %eax
	btsl	$0, %eax	# PE
#ifdef	BITS64
	btsl	$31, %eax	# PG
#endif
	movl	%eax, %cr0		# OK!!!

#ifdef	BITS64
jump_to_lmode:
	.byte	0x66, 0xEA
	.long	lmode_start
	.word	0x0008
#else
jump_to_pmode:			# same as : ljmp $0x0008, $pmode_start
	.byte	0x66, 0xEA	# but, it will be failed  work if
	.long	pmode_start	# <<-THIS is greater than 0xFFFF.
	.word	0x0008		# this is because the assembler is in
				# real mode (.code16), it does not
				# understand 32-bit opcode. so we use
				# .byte, .word and .long instead
				# to create a 32-bit opcode
#endif

error:
fin:	hlt
	jmp	fin

delay:	outb	%al, $0x80
	ret

putsth:	movw	$msg_sth, %si
	call	print_bios
	ret

msg_sth:	.ascii	"Hello??\0"

	.align	2

gdtr0:
	.word	gdt0_len
	#.long	0	# will be filled later
	.long	0x80000

idtr0:			# will reloaded later
	.word	0
	.long	0

	.align	8

gdt0:
	.quad	0x0000000000000000
#ifdef	BITS64
	.quad	0x0020980000000000
	.quad	0x0000920000000001
#else
	.quad	0x00CF9A000000FFFF
	.quad	0x00CF92000000FFFF
#endif
	.quad	0x0000000000000000
	.quad	0x0000000000000000

.equ	gdt0_len,	. - gdt0 - 1

print_bios:
	movb	$0x0E, %ah
print_bios_loop:
	lodsb
	testb	%al, %al
	jz	print_bios_done
	int	$0x10
	jmp	print_bios_loop
print_bios_done:
	ret

start_datas:
msg_start:	.ascii	"Kernel started\r\n\0"

	.org	0x1000, 0
stack_top:

