#pragma once


#ifdef	_KERN_MAKE
#define	KBUILDING	1
#endif

#if	_CC == tcc
#define	_TCC	1
#elif	_CC == gcc
#define	_GCC	1
#endif

#include	"unistd.h"


