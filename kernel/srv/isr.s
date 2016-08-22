.text
.globl	isr_route
.globl	isr_entry_tab
.globl	isr_tab

isr_route:
	pushw	%ds
	pushw	%es
	pushw	%fs
	pushw	%gs
	pushal
	movw	%ss, %ax
	movw	%ax, %ds
	movw	%ax, %es
	movw	%ax, %fs
	movw	%ax, %gs
	movl	48(%esp), %eax	# isr_nr, index number
	call	*isr_tab(, %eax, 4)
	popal
	popw	%gs
	popw	%fs
	popw	%es
	popw	%ds
	iretl

isr_entry_int0x00:
	pushw	$0
	pushw	$0x00
	jmp	isr_route
isr_entry_int0x01:
	pushw	$0
	pushw	$0x01
	jmp	isr_route
isr_entry_int0x02:
	pushw	$0
	pushw	$0x02
	jmp	isr_route
isr_entry_int0x03:
	pushw	$0
	pushw	$0x03
	jmp	isr_route
isr_entry_int0x04:
	pushw	$0
	pushw	$0x04
	jmp	isr_route
isr_entry_int0x05:
	pushw	$0
	pushw	$0x05
	jmp	isr_route
isr_entry_int0x06:
	pushw	$0
	pushw	$0x06
	jmp	isr_route
isr_entry_int0x07:
	pushw	$0
	pushw	$0x07
	jmp	isr_route
isr_entry_int0x08:
	pushw	$0
	pushw	$0x08
	jmp	isr_route
isr_entry_int0x09:
	pushw	$0
	pushw	$0x09
	jmp	isr_route
isr_entry_int0x0a:
	pushw	$0
	pushw	$0x0a
	jmp	isr_route
isr_entry_int0x0b:
	pushw	$0
	pushw	$0x0b
	jmp	isr_route
isr_entry_int0x0c:
	pushw	$0
	pushw	$0x0c
	jmp	isr_route
isr_entry_int0x0d:
	pushw	$0
	pushw	$0x0d
	jmp	isr_route
isr_entry_int0x0e:
	pushw	$0
	pushw	$0x0e
	jmp	isr_route
isr_entry_int0x0f:
	pushw	$0
	pushw	$0x0f
	jmp	isr_route
isr_entry_int0x10:
	pushw	$0
	pushw	$0x10
	jmp	isr_route
isr_entry_int0x11:
	pushw	$0
	pushw	$0x11
	jmp	isr_route
isr_entry_int0x12:
	pushw	$0
	pushw	$0x12
	jmp	isr_route
isr_entry_int0x13:
	pushw	$0
	pushw	$0x13
	jmp	isr_route
isr_entry_int0x14:
	pushw	$0
	pushw	$0x14
	jmp	isr_route
isr_entry_int0x15:
	pushw	$0
	pushw	$0x15
	jmp	isr_route
isr_entry_int0x16:
	pushw	$0
	pushw	$0x16
	jmp	isr_route
isr_entry_int0x17:
	pushw	$0
	pushw	$0x17
	jmp	isr_route
isr_entry_int0x18:
	pushw	$0
	pushw	$0x18
	jmp	isr_route
isr_entry_int0x19:
	pushw	$0
	pushw	$0x19
	jmp	isr_route
isr_entry_int0x1a:
	pushw	$0
	pushw	$0x1a
	jmp	isr_route
isr_entry_int0x1b:
	pushw	$0
	pushw	$0x1b
	jmp	isr_route
isr_entry_int0x1c:
	pushw	$0
	pushw	$0x1c
	jmp	isr_route
isr_entry_int0x1d:
	pushw	$0
	pushw	$0x1d
	jmp	isr_route
isr_entry_int0x1e:
	pushw	$0
	pushw	$0x1e
	jmp	isr_route
isr_entry_int0x1f:
	pushw	$0
	pushw	$0x1f
	jmp	isr_route
isr_entry_int0x20:
	pushw	$0
	pushw	$0x20
	jmp	isr_route
isr_entry_int0x21:
	pushw	$0
	pushw	$0x21
	jmp	isr_route
isr_entry_int0x22:
	pushw	$0
	pushw	$0x22
	jmp	isr_route
isr_entry_int0x23:
	pushw	$0
	pushw	$0x23
	jmp	isr_route
isr_entry_int0x24:
	pushw	$0
	pushw	$0x24
	jmp	isr_route
isr_entry_int0x25:
	pushw	$0
	pushw	$0x25
	jmp	isr_route
isr_entry_int0x26:
	pushw	$0
	pushw	$0x26
	jmp	isr_route
isr_entry_int0x27:
	pushw	$0
	pushw	$0x27
	jmp	isr_route
isr_entry_int0x28:
	pushw	$0
	pushw	$0x28
	jmp	isr_route
isr_entry_int0x29:
	pushw	$0
	pushw	$0x29
	jmp	isr_route
isr_entry_int0x2a:
	pushw	$0
	pushw	$0x2a
	jmp	isr_route
isr_entry_int0x2b:
	pushw	$0
	pushw	$0x2b
	jmp	isr_route
isr_entry_int0x2c:
	pushw	$0
	pushw	$0x2c
	jmp	isr_route
isr_entry_int0x2d:
	pushw	$0
	pushw	$0x2d
	jmp	isr_route
isr_entry_int0x2e:
	pushw	$0
	pushw	$0x2e
	jmp	isr_route
isr_entry_int0x2f:
	pushw	$0
	pushw	$0x2f
	jmp	isr_route
isr_entry_int0x30:
	pushw	$0
	pushw	$0x30
	jmp	isr_route
isr_entry_int0x31:
	pushw	$0
	pushw	$0x31
	jmp	isr_route
isr_entry_int0x32:
	pushw	$0
	pushw	$0x32
	jmp	isr_route

isr_entry_tab:
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

isr_tab:
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

