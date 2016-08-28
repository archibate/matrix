/*
 * kernel Standard C library : string
 */
#include	"../kernel.h"
#include	"string.h"
#include	"memory.h"


#ifndef	_FL_CC_tcc
char	*strcpy(
		char		*dst,
		const char	*src
	       )
{
	__asm__ (	"0:"
			"lodsb\n"
			"testb	%%al, %%al\n"
			"jz	1f\n"
			"stosb\n"
			"jmp	0b\n"
			"1:" ::
			"D" (dst),
			"S" (src)
		);
	return dst;
}


char	*strcat(
		char		*dst,
		const char	*src
	       )
{
	__asm__ (	"2:"
			"lodsb\n"
			"testb	%%al, %%al\n"
			"jnz	2b\n"
			"3:"
			"lodsb\n"
			"testb	%%al, %%al\n"
			"jz	3b\n"
			"stosb\n"
			"jmp	4f\n"
			"4:" ::
			"D" (dst),
			"S" (src)
		);
	return dst;
}


size_t	strlen(
		const char	*str
	      )
{
	char	*end;
	__asm__ (	"5:"
			"lodsb\n"
			"testb	%%al, %%al\n"
			"jnz	5b\n" :
			"=S" (end) :
			"S" (str)
		);
	return (int) (end - str);
}
#endif


