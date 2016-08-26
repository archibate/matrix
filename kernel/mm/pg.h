#pragma once

#include	"../mm/mm.h"

#define	L2PT_PAD	0x00004000
#define	L2PT_PAPV	((u32 *) L2PT_PAD)
#define	L1PT0_PAD	0x00050000
#define	L1PT0_PAPV	((u32 *) L1PT0_PAD)
#define	L1PT_MAX	0x1000
#define	PA_P		1
#define	PA_W		2
#define	PA_U		4

typedef	u16	u10;
typedef	u16	u12;

#define	lea_usr_lin(cr3, lin) \
	0


void	init_pg();
void	remapg(
		u32	phy,
		u32	lin);
void	remapgs(
		u32	phy,
		u32	lin,
		u32	count);


