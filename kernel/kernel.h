#pragma once


#ifdef	_KERN_MAKE
#define	KBUILDING	1
#endif
#ifdef	_BITS64
#define	BITS64	1
#endif
#ifndef	_CC
#error	macro '_CC' should be supplied in Makefile.header
#endif
#if	_CC == tcc
#define	_TCC	1
#elif	_CC == gcc
#define	_GCC	1
#else
#error
#endif

#include	"unistd.h"


