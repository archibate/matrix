#pragma once


#define	GDT_PAD		0x00001800
#define	IDT_PAD		0x00001000
#define	GDT_PAPV	(* (u64 *) GDT_PAD)
#define	IDT_PAPV	(* (u64 *) IDT_PAD)


void	init_gdt();


