[BITS 16]
[SECTION .text]

	org	0x7C00

_start:
	jmp	main

main:
	mov	si, msg_nonsys
	call	print
	mov	ah, 0
	int	0x16
	int	0x19		; hot reset
	jmp	0xF000 : 0xFFF0	; cold reboot

print:
	mov	ah, 0x0E
	jmp	print_begin
print_loop:
	int	0x10
print_begin:
	lodsb
	test	al, al
	jnz	print_loop
	ret

msg_nonsys:
	db	"ERROR : This is an Non-System Disk, "
	db	"please insert another Bootable Disk and "
	db	"press ENTER", 10, 13, 0

	resb	510 - ($ - $$)
	dw	0xAA55

