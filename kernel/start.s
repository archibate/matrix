.text
.code16
.global	_start

_start:
	movw	$0x0E4F, %ax
	int	$0x10
	movw	$0x0E4B, %ax
	int	$0x10
	cli
	hlt

