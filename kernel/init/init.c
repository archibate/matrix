#include	"../kernel.h"
#include	"desc.h"
#include	"pic.h"
#include	"../tt/tt.h"
#include	"../tty/ttyio.h"
#include	"../mm/mm.h"
#include	"../mm/pg.h"
#include	"../lib/memory.h"
#include	"../asf.h"


void	smi_handler();


void	init(void)	/* init() were called from start.s */
{
	//(* (u16 *) 0x000B8000) = 0x0C03;

	init_gdt();
	init_idt();
	init_pic();
	init_pit();
	init_pg();
	init_tt();
	clean_screen();
	printstr("Hello, TelType!\r\nI'm MATRIX!\r\n", 0x07);
	//io_sti();
	//tt_iret();
	char	cpu_builder[13] = {0};
	u32	max_basic_leafs;
	u32	max_extended_leafs;
	u32	cpu_fms_info;
	u32	cpu_ebx_info;
	u32	cpu_ecx_info;
	u32	cpu_edx_info;
	u32	cpu_extnd1_eax_info;
	u32	cpu_extnd1_ebx_info;
	u32	cpu_extnd1_ecx_info;
	u32	cpu_extnd1_edx_info;
	u32	cpu_family;
	u32	displ_family;
	u32	extnd_family;
	u32	cpu_model;
	u32	extnd_model;
	u32	displ_model;
	u32	cpu_plbus_info;
	u32	cpu_logic_procrs;
	u32	cpu_cache_lnsize;
	u32	cpu_pro_ext_sta_lo;
	u32	cpu_pro_ext_sta_hi;
	u32	cpu_supp_monitor;
	u32	cpu_supp_longmode;
	u32	cpu_supp_1gpage;
	u32	cpu_supp_pcid;
	u32	cpu_supp_sse;
	u32	cpu_supp_ymm;
	u32	cpu_supp_fpu;
	u32	mtrr_fix64k_00000;
	u32	mtrr_fix16k_80000;
	u32	mtrr_fix16k_A0000;
	__asm__ (	"xorl	%%eax, %%eax\n"
			"cpuid\n"
			"movl	%%ebx, (%%edi)\n"
			"movl	%%edx, 4(%%edi)\n"
			"movl	%%ecx, 8(%%edi)\n"
			: "=eax" (max_basic_leafs)
			: "D" (cpu_builder));
	__asm__ (	"movl	$0x80000000, %%eax\n"
			"cpuid\n"
			: "=eax" (max_extended_leafs) : );
	__asm__ (	"movl	$0x01, %%eax\n"
			"cpuid\n"
			: "=eax" (cpu_fms_info),
			"=ebx" (cpu_ebx_info),
			"=ecx" (cpu_ecx_info),
			"=edx" (cpu_edx_info) : );
	__asm__ (	"movl	$0x80000001, %%eax\n"
			"cpuid\n"
			: "=eax" (cpu_extnd1_eax_info),
			"=ebx" (cpu_extnd1_ebx_info),
			"=ecx" (cpu_extnd1_ecx_info),
			"=edx" (cpu_extnd1_edx_info) : );
	displ_family = cpu_family = (cpu_fms_info & 0xF00) >> 8;
	displ_model = cpu_model = (cpu_fms_info & 0xF0) >> 4;
	extnd_family = (cpu_fms_info & 0xFF0000) >> 20;
	extnd_model = (cpu_fms_info & 0xF0000) >> 16;
	cpu_cache_lnsize = (cpu_ebx_info & 0xFF00) >> 5;
	cpu_logic_procrs = (cpu_ebx_info & 0xFF0000) >> 16;
	cpu_supp_monitor = (cpu_ecx_info & (1 << 3)) ? 1 : 0;
	cpu_supp_longmode = (cpu_extnd1_edx_info & (1 << 29)) ? 1 : 0;
	cpu_supp_1gpage = (cpu_extnd1_edx_info & (1 << 26)) ? 1 : 0;
	cpu_supp_pcid = (cpu_ecx_info & (1 << 17)) ? 1 : 0;
	if (cpu_family == 0x0F) {
		displ_family += extnd_family;
		displ_model += extnd_model << 4;
	}
	if (cpu_family == 0x06) {
		displ_model += extnd_model << 4;
	}
	if (max_basic_leafs >= 0x0D/* || 1*/) {
		__asm__ (	"movl	$0x0D, %%eax\n"
				"movl	$0, %%ecx\n"
				"cpuid\n"
				/*: "=eax" (* (u32 *) &cpu_pro_ext_sta),
				  "=edx" (* ((u32 *) &cpu_pro_ext_sta
						+ 1)) :*/
				: "=eax" (cpu_pro_ext_sta_lo),
				"=edx" (cpu_pro_ext_sta_hi) : );
	} else {
		cpu_pro_ext_sta_lo = cpu_pro_ext_sta_hi = 0;
	}
	cpu_supp_fpu = cpu_pro_ext_sta_lo & (1 << 1);
	cpu_supp_sse = cpu_pro_ext_sta_lo & (1 << 2);
	cpu_supp_ymm = cpu_pro_ext_sta_lo & (1 << 3);
	if (max_extended_leafs >= 0x80000008) {
		__asm__ (	"movl	$0x80000008, %%eax\n"
				"cpuid\n"
				: "=eax" (cpu_plbus_info) : );
	} else {
		cpu_plbus_info = 0;
	}
	if (cpu_supp_longmode) {
		/*__asm__ (	"movl	$0xC0000080, %%ecx\n"
				"rdmsr\n"
				"bts	$8, %%eax\n"
				"wrmsr\n"
				"rdmsr\n"
				"bt	$8, %%eax\n"
				"jnc	." :: );*/
	}
	/*__asm__ (	"movl	$0x250, %%ecx\n"
			"rdmsr\n"
			: "=eax" (mtrr_fix64k_00000) : );
	__asm__ (	"movl	$0x250, %%ecx\n"
			"wrmsr\n"
			:: "eax" (mtrr_fix64k_00000 | 0x06));
	__asm__ (	"movl	$0x250, %%ecx\n"
			"rdmsr\n"
			: "=eax" (mtrr_fix64k_00000) : );*/
	mtrr_fix64k_00000 = io_rdmsr(0x250);
	mtrr_fix16k_80000 = io_rdmsr(0x258);
	mtrr_fix16k_A0000 = io_rdmsr(0x259);
	//io_wrmsr(mtrr_fix64k_00000, 0x250);
	//mtrr_fix64k_00000 = io_rdmsr(0x250);
	printk("CPU : %s %s %s", cpu_builder,
			cpu_family == 0x06 ? "Pentium6" :
			(cpu_family == 0x0F ? "Pentium4" :
			("Unknown")), cpu_supp_longmode ?
			"x64" : "x86");
	//io_cli(); io_hlt();
	printk("CPU Family : %s (No. 0x%02X)",
			cpu_family == 0x06 ? "Pentium6" :
			(cpu_family == 0x0F ? "Pentium4" :
			("Unknown")), cpu_family);
	printk("CPU FMS Info Number : 0x%08X", cpu_fms_info);
	printk("CPU Display Family Number : 0x%03X", displ_family);
	printk("CPU Display Model Number : 0x%02X", displ_model);
	if (cpu_plbus_info) {
		printk("Physical Address Max Width : %d bits",
				cpu_plbus_info & 0xFF);
		printk("Linear Address Max Width : %d bits",
				(cpu_plbus_info & 0xFF00) >> 8);
	}
	if (cpu_logic_procrs) {
		printk("Logic Processor(s) : %d", cpu_logic_procrs);
	}
	printk("Maximium Basic Leafs : 0x%08X", max_basic_leafs);
	printk("Maximium Extended Leafs : 0x8%07X",
			max_extended_leafs - 0x80000000);
	printk("CPU Cache line size : %dB (0x%04X)",
			cpu_cache_lnsize, cpu_cache_lnsize);
	if (cpu_pro_ext_sta_lo || cpu_pro_ext_sta_hi) {
		printk("Processor Extened State : 0x%08X_%08X",
				cpu_pro_ext_sta_hi, cpu_pro_ext_sta_lo);
	}
	printk("CPU Supports : %s %s %s %s %s %s %s",
			cpu_supp_longmode ? "LONGMODE" : "longmode",
			cpu_supp_1gpage ? "1G_PAGE" : "1g_page",
			cpu_supp_monitor ? "MONITOR" : "monitor",
			cpu_supp_pcid ? "PCID" : "pcid",
			cpu_supp_fpu ? "FPU" : "fpu",
			cpu_supp_sse ? "SSE" : "sse",
			cpu_supp_ymm ? "YMM" : "ymm");
	memcpy((void *) 0x38000, (void *) (r_t) smi_handler, 100);
	io_outw(0x2001, 0x1004);
	/*while (io_inb(0x64) & 0x02);
	io_outb(0xFE, 0x64);*/
	io_outb(0x00, 0xB2);
	//io_sti();
	panic("hi");
	//printk("IA32_MTRR_FIX64K_00000 : %08X", mtrr_fix64k_00000);
	r_t	addr;
	u32	marker;
	u8	type;
	for (addr = 0x00000, marker = 0xFF; addr < 0x80000;
			addr += 0x10000, marker <<= 8) {
		type = mtrr_fix64k_00000 & marker;
		printk("0x%05X-%05X | 0x%02X/%s", addr,
				addr + 0x0FFFF, type,
				(type == 0x00 ? "Uncacheable    (UC)" :
				(type == 0x04 ? "WriteThrough   (WT)" :
				(type == 0x06 ? "WriteBack      (WB)" :
				(type == 0x05 ? "WriteProtected (WP)" :
				(type == 0x01 ? "WriteCombining (WC)" :
				"<Invalid>"))))));
	}
	for (addr = 0x80000, marker = 0xFF; addr < 0xA0000;
			addr += 0x04000, marker <<= 8) {
		type = mtrr_fix16k_80000 & marker;
		printk("0x%05X-%05X | 0x%02X/%s", addr,
				addr + 0x003FF, type,
				(type == 0x00 ? "Uncacheable    (UC)" :
				(type == 0x04 ? "WriteThrough   (WT)" :
				(type == 0x06 ? "WriteBack      (WB)" :
				(type == 0x05 ? "WriteProtected (WP)" :
				(type == 0x01 ? "WriteCombining (WC)" :
				"<Invalid>"))))));
	}
	for (addr = 0xA0000, marker = 0xFF; addr < 0xC0000;
			addr += 0x04000, marker <<= 8) {
		type = mtrr_fix16k_A0000 & marker;
		printk("0x%05X-%05X | 0x%02X/%s", addr,
				addr + 0x003FF, type,
				(type == 0x00 ? "Uncacheable    (UC)" :
				(type == 0x04 ? "WriteThrough   (WT)" :
				(type == 0x06 ? "WriteBack      (WB)" :
				(type == 0x05 ? "WriteProtected (WP)" :
				(type == 0x01 ? "WriteCombining (WC)" :
				"<Invalid>"))))));
	}/**/
	/*clean_screen();
	memset_word(VRAM, 0x1700, TTY_XS * TTY_YS);
	printstr("\r\n  An ERROR occured durning the initialize stage.\r\n", 0x17);
	printstr("\r\n  If you have seen this before, please contact me at 4008-517-517\r\n", 0x17);
	printstr("\r\n\r\n  Core dumped :\r\n\r\n        #0043BE12  #55621F34\r\n        #24E4D625  #A07B5647\r\n\r\n", 0x17);
	panic("BLUE OF THE DEATH");*/

	//__asm__ ("int	$0x30");

	/*for (;;) {
		__asm__ ("pause");
	}*/

	//tt_iret();

	for (;;) {
		io_hlt();
	}
}


