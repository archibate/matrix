.text
.globl	isr_route
.globl	isr_entry_tab
.globl	isr_tab

/*
--------------- 76
ESP/?		72
SS/?		68
EIP		64
CS		60
EFL		56
ERR_CODE/0	52
ISR_NR		48 <-+
EAX		44   |
ECX		40   |
EDX		36   |
EBX		32   |
NEW_ESP		28 --+
EBP		24
ESI		20
EDI		16
DS		12
ES		8
FS		4
GS		0  <- ESP NOW
*/

isr_route:		# the sharing part of all ISRs
	pushal
	pushl	%ds	# NOTE : although segment registers are 16-bit,
	pushl	%es	# but in order to avoid errors,
	pushl	%fs	# we push them as 32-bit register
	pushl	%gs

	movw	%ss, %ax	# CPU has set %ss to kernel mode automaticly
	movw	%ax, %ds
	movw	%ax, %es
	movw	%ax, %fs
	movw	%ax, %gs

	movl	48(%esp), %eax	# isr_nr - ISR index number
	call	*isr_tab(, %eax, 4)

	popl	%gs
	popl	%fs
	popl	%es
	popl	%ds
	popal
	addl	$8, %esp	# skip isr_nr and err_code
	iretl

	# CPU push 'error code' to stack in some ISRs : 0x08, 0x0A, etc.
	# and the others do not have.
	# in these ISRs without 'error code', we (software) push 0 instead.

isr_entry_int0x00:
	pushl	$0
	pushl	$0x00		# push index, isr_route will deal it
	jmp	isr_route
isr_entry_int0x01:
	pushl	$0
	pushl	$0x01
	jmp	isr_route
isr_entry_int0x02:
	pushl	$0
	pushl	$0x02
	jmp	isr_route
isr_entry_int0x03:
	pushl	$0
	pushl	$0x03
	jmp	isr_route
isr_entry_int0x04:
	pushl	$0
	pushl	$0x04
	jmp	isr_route
isr_entry_int0x05:
	pushl	$0
	pushl	$0x05
	jmp	isr_route
isr_entry_int0x06:
	pushl	$0
	pushl	$0x06
	jmp	isr_route
isr_entry_int0x07:
	pushl	$0
	pushl	$0x07
	jmp	isr_route
isr_entry_int0x08:
	pushl	$0x08
	jmp	isr_route
isr_entry_int0x09:
	pushl	$0
	pushl	$0x09
	jmp	isr_route
isr_entry_int0x0a:
	pushl	$0x0a
	jmp	isr_route
isr_entry_int0x0b:
	pushl	$0x0b
	jmp	isr_route
isr_entry_int0x0c:
	pushl	$0x0c
	jmp	isr_route
isr_entry_int0x0d:
	pushl	$0x0d
	jmp	isr_route
isr_entry_int0x0e:
	pushl	$0x0e
	jmp	isr_route
isr_entry_int0x0f:
	pushl	$0
	pushl	$0x0f
	jmp	isr_route
isr_entry_int0x10:
	pushl	$0x10
	jmp	isr_route
isr_entry_int0x11:
	pushl	$0
	pushl	$0x11
	jmp	isr_route
isr_entry_int0x12:
	pushl	$0
	pushl	$0x12
	jmp	isr_route
isr_entry_int0x13:
	pushl	$0
	pushl	$0x13
	jmp	isr_route
isr_entry_int0x14:
	pushl	$0
	pushl	$0x14
	jmp	isr_route
isr_entry_int0x15:
	pushl	$0
	pushl	$0x15
	jmp	isr_route
isr_entry_int0x16:
	pushl	$0
	pushl	$0x16
	jmp	isr_route
isr_entry_int0x17:
	pushl	$0
	pushl	$0x17
	jmp	isr_route
isr_entry_int0x18:
	pushl	$0
	pushl	$0x18
	jmp	isr_route
isr_entry_int0x19:
	pushl	$0
	pushl	$0x19
	jmp	isr_route
isr_entry_int0x1a:
	pushl	$0
	pushl	$0x1a
	jmp	isr_route
isr_entry_int0x1b:
	pushl	$0
	pushl	$0x1b
	jmp	isr_route
isr_entry_int0x1c:
	pushl	$0
	pushl	$0x1c
	jmp	isr_route
isr_entry_int0x1d:
	pushl	$0
	pushl	$0x1d
	jmp	isr_route
isr_entry_int0x1e:
	pushl	$0
	pushl	$0x1e
	jmp	isr_route
isr_entry_int0x1f:
	pushl	$0
	pushl	$0x1f
	jmp	isr_route
isr_entry_int0x20:
	pushl	$0
	pushl	$0x20
	jmp	isr_route
isr_entry_int0x21:
	pushl	$0
	pushl	$0x21
	jmp	isr_route
isr_entry_int0x22:
	pushl	$0
	pushl	$0x22
	jmp	isr_route
isr_entry_int0x23:
	pushl	$0
	pushl	$0x23
	jmp	isr_route
isr_entry_int0x24:
	pushl	$0
	pushl	$0x24
	jmp	isr_route
isr_entry_int0x25:
	pushl	$0
	pushl	$0x25
	jmp	isr_route
isr_entry_int0x26:
	pushl	$0
	pushl	$0x26
	jmp	isr_route
isr_entry_int0x27:
	pushl	$0
	pushl	$0x27
	jmp	isr_route
isr_entry_int0x28:
	pushl	$0
	pushl	$0x28
	jmp	isr_route
isr_entry_int0x29:
	pushl	$0
	pushl	$0x29
	jmp	isr_route
isr_entry_int0x2a:
	pushl	$0
	pushl	$0x2a
	jmp	isr_route
isr_entry_int0x2b:
	pushl	$0
	pushl	$0x2b
	jmp	isr_route
isr_entry_int0x2c:
	pushl	$0
	pushl	$0x2c
	jmp	isr_route
isr_entry_int0x2d:
	pushl	$0
	pushl	$0x2d
	jmp	isr_route
isr_entry_int0x2e:
	pushl	$0
	pushl	$0x2e
	jmp	isr_route
isr_entry_int0x2f:
	pushl	$0
	pushl	$0x2f
	jmp	isr_route
isr_entry_int0x30:
	pushl	$0
	pushl	$0x30
	jmp	isr_route
isr_entry_int0x31:
	pushl	$0
	pushl	$0x31
	jmp	isr_route
isr_entry_int0x32:
	pushl	$0
	pushl	$0x32
	jmp	isr_route

isr_entry_tab:				# table of entry, use for init/desc.c
	.long	isr_entry_int0x00
	.long	isr_entry_int0x01
	.long	isr_entry_int0x02
	.long	isr_entry_int0x03
	.long	isr_entry_int0x04
	.long	isr_entry_int0x05
	.long	isr_entry_int0x06
	.long	isr_entry_int0x07
	.long	isr_entry_int0x08
	.long	isr_entry_int0x09
	.long	isr_entry_int0x0a
	.long	isr_entry_int0x0b
	.long	isr_entry_int0x0c
	.long	isr_entry_int0x0d
	.long	isr_entry_int0x0e
	.long	isr_entry_int0x0f
	.long	isr_entry_int0x10
	.long	isr_entry_int0x11
	.long	isr_entry_int0x12
	.long	isr_entry_int0x13
	.long	isr_entry_int0x14
	.long	isr_entry_int0x15
	.long	isr_entry_int0x16
	.long	isr_entry_int0x17
	.long	isr_entry_int0x18
	.long	isr_entry_int0x19
	.long	isr_entry_int0x1a
	.long	isr_entry_int0x1b
	.long	isr_entry_int0x1c
	.long	isr_entry_int0x1d
	.long	isr_entry_int0x1e
	.long	isr_entry_int0x1f
	.long	isr_entry_int0x20
	.long	isr_entry_int0x21
	.long	isr_entry_int0x22
	.long	isr_entry_int0x23
	.long	isr_entry_int0x24
	.long	isr_entry_int0x25
	.long	isr_entry_int0x26
	.long	isr_entry_int0x27
	.long	isr_entry_int0x28
	.long	isr_entry_int0x29
	.long	isr_entry_int0x2a
	.long	isr_entry_int0x2b
	.long	isr_entry_int0x2c
	.long	isr_entry_int0x2d
	.long	isr_entry_int0x2e
	.long	isr_entry_int0x2f
	.long	isr_entry_int0x30
	.long	isr_entry_int0x31
	.long	isr_entry_int0x32

isr_tab:			# ISR handlers in srv/isr.c 
	.long	isr_int0x00
	.long	isr_int0x01
	.long	isr_int0x02
	.long	isr_int0x03
	.long	isr_int0x04
	.long	isr_int0x05
	.long	isr_int0x06
	.long	isr_int0x07
	.long	isr_int0x08
	.long	isr_int0x09
	.long	isr_int0x0a
	.long	isr_int0x0b
	.long	isr_int0x0c
	.long	isr_int0x0d
	.long	isr_int0x0e
	.long	isr_int0x0f
	.long	isr_int0x10
	.long	isr_int0x11
	.long	isr_int0x12
	.long	isr_int0x13
	.long	isr_int0x14
	.long	isr_int0x15
	.long	isr_int0x16
	.long	isr_int0x17
	.long	isr_int0x18
	.long	isr_int0x19
	.long	isr_int0x1a
	.long	isr_int0x1b
	.long	isr_int0x1c
	.long	isr_int0x1d
	.long	isr_int0x1e
	.long	isr_int0x1f
	.long	isr_int0x20
	.long	isr_int0x21
	.long	isr_int0x22
	.long	isr_int0x23
	.long	isr_int0x24
	.long	isr_int0x25
	.long	isr_int0x26
	.long	isr_int0x27
	.long	isr_int0x28
	.long	isr_int0x29
	.long	isr_int0x2a
	.long	isr_int0x2b
	.long	isr_int0x2c
	.long	isr_int0x2d
	.long	isr_int0x2e
	.long	isr_int0x2f
	.long	isr_int0x30
	.long	isr_int0x31
	.long	isr_int0x32

