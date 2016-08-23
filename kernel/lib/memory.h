/*
 * src/kernel/lib/memory.c
 * - 内存处理相关的函数，一些用宏来实现
 */
#pragma once


#define	memcpy_byte(dst, src, cnt) \
	__asm__ (	"cld\nrep\nmovsb" :: \
			"D" (dst), \
			"S" (src), \
			"c" (cnt) \
		)

#define	memset_byte(dst, val, cnt) \
	__asm__ (	"cld\nrep\nstosb" :: \
			"D" (dst), \
			"a" (val), \
			"c" (cnt) \
	    )

#define	memcpy_word(dst, src, cnt) \
	__asm__ (	"cld\nrep\nmovsw" :: \
			"D" (dst), \
			"S" (src), \
			"c" (cnt) \
		)

#define	memset_word(dst, val, cnt) \
	__asm__ (	"cld\nrep\nstosw" :: \
			"D" (dst), \
			"a" (val), \
			"c" (cnt) \
	    )

#define	memcpy_long(dst, src, cnt) \
	__asm__ (	"cld\nrep\nmovsl" :: \
			"D" (dst), \
			"S" (src), \
			"c" (cnt) \
		)

#define	memrevcpy_byte(dst, src, cnt) \
	__asm__ (	"addl	%%ecx, %%esi\n" \
			"addl	%%ecx, %%edi\n" \
			"std\nrep\nmovsb" :: \
			"D" (dst), \
			"S" (src), \
			"c" (cnt) \
		)

#define	memrevcpy_word(dst, src, cnt) \
	__asm__ (	"movl	%%eax, %%ecx\n" \
			"shrl	$1, %%eax\n" \
			"addl	%%eax, %%esi\n" \
			"addl	%%eax, %%edi\n" \
			"std\nrep\nmovsw" :: \
			"D" (dst), \
			"S" (src), \
			"a" (cnt) \
		)

#define	memrevcpy_long(dst, src, cnt) \
	__asm__ (	"movl	%%eax, %%ecx\n" \
			"shrl	$2, %%eax\n" \
			"addl	%%eax, %%esi\n" \
			"addl	%%eax, %%edi\n" \
			"std\nrep\nmovsl" :: \
			"D" (dst), \
			"S" (src), \
			"a" (cnt) \
		)

#define	memmove_byte(dst, src, cnt) \
	__asm__ (	"cld\n" \
			"cmpl	%%esi, %%edi\n" \
			"jb	.1\n" \
			"je	.2\n" \
			"addl	%%ecx, %%esi\n" \
			"addl	%%ecx, %%edi\n" \
			"std\n.1:" \
			"rep\nmovsb\n.2:" :: \
			"D" (dst), \
			"S" (src), \
			"c" (cnt) \
		)

#define	memmove_word(dst, src, cnt) \
	__asm__ (	"cld\n" \
			"cmpl	%%esi, %%edi\n" \
			"jb	.1\n" \
			"je	.2\n" \
			"movl	%%ecx, %%eax\n" \
			"shrl	$1, %%eax\n" \
			"addl	%%eax, %%esi\n" \
			"addl	%%eax, %%edi\n" \
			"std\n.1:" \
			"rep\nmovsw\n.2:" :: \
			"D" (dst), \
			"S" (src), \
			"c" (cnt) \
		)

#define	memmove_long(dst, src, cnt) \
	__asm__ (	"cld\n" \
			"cmpl	%%esi, %%edi\n" \
			"jb	.1\n" \
			"je	.2\n" \
			"movl	%%ecx, %%eax\n" \
			"shrl	$2, %%eax\n" \
			"addl	%%eax, %%esi\n" \
			"addl	%%eax, %%edi\n" \
			"std\n.1:" \
			"rep\nmovsl\n.2:" :: \
			"D" (dst), \
			"S" (src), \
			"c" (cnt) \
		)

#define	memset_long(dst, val, cnt) \
	__asm__ (	"cld\nrep\nstosl" :: \
			"D" (dst), \
			"a" (val), \
			"c" (cnt) \
	    )


void	*memcpy(
		void		*dst,
		const void	*src,
		size_t		cnt
	       );
void	*memset(
		void		*dst,
#ifdef	__GNUC__
		int		val,
#else
		u8		val,
#endif
		size_t		cnt
	       );
void	*memmove(
		void		*dst,
		const void	*src,
		size_t		cnt
	       );
int	memcmp(
		const void	*dst,
		const void	*src,
		size_t		cnt
	       );

