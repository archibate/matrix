/* string.c
* - 内核的标准库：字符串的处理：
*   strcpy, strcat, strcmp, strlen
*/
#include	"../kernel.h"
#include	"string.h"
#include	"memory.h"

// 一定还有可以改进的地方


#ifndef	_FL_CC_tcc
char	*strcpy(
		char		*dst,
		const char	*src
	       )
{
	__asm__ (	".0:"
			"lodsb\n"
			"testb	%%al, %%al\n"
			"jz	.1\n"
			"stosb\n"
			"jmp	.0\n"
			".1:" ::
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
	__asm__ (	".2:"
			"lodsb\n"
			"testb	%%al, %%al\n"
			"jnz	.2\n"
			".3:"
			"lodsb\n"
			"testb	%%al, %%al\n"
			"jz	.3\n"
			"stosb\n"
			"jmp	.4\n"
			".4:" ::
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
	__asm__ (	".5:"
			"lodsb\n"
			"testb	%%al, %%al\n"
			"jnz	.5\n" :
			"=S" (end) :
			"S" (str)
		);
	return (int) (end - str);
}
#endif


