#include	"../kernel.h"
#include	"fs.h"
#include	"../tt/tt.h"
#include	"../tty/ttyio.h"
#include	"../asf.h"
#include	"../mm/mm.h"
#include	"../lib/memory.h"
#include	"../lib/string.h"


void	init_hd()
{
}


void	fs_daemon()
{
	pid_t	sender;
	static int	recv_buf[1];
	static size_t	recv_size;
	extern struct task	*task_ready;
	//extern struct task	*tasks;

	init_hd();
	strcpy(task_ready->name, "FS");
	//printk("Devices count in BIOS Data Area : %d", * (u8 *) 0x475);

	for (;;) {
		memset(recv_buf, 0, recv_size = sizeof(recv_buf));
		sender = tt_recvs(0, recv_buf, &recv_size);
		sender = sender + 1 - 1;

		switch (recv_buf[0]) {
		case FS_SCNR_dev_open:
			hd_drive_identify(0);	/* /dev/hd0 */
			continue;
		default:
			printk("System Call Error : %d is not an index of FS SysCall",
					recv_buf[0]);
			continue;
		}
	}

}


void	hd_drive_identify(
		int	drv_nr)
{
	static struct hd_cmd	cmd;
	static u8	buf[512];
	memset(&cmd, 0, sizeof(cmd));
	cmd.dev		= get_device_nr(0, drv_nr, 0);
	cmd.cmd		= 0x20;		/* Read */
	cmd.count	= 1;
	hd_command(&cmd);
	wait_hd_irq();
	io_insl(0x1F0, buf, 128);
	for (size_t i = 0; i < sizeof(buf) / 16; ++i) {
		printf("%02X ", buf[i]);
		if (i % 24 == 23)
			printf("\r\n");
	}
	printf("\r\n");
	panic("sfadasd");

	cmd.dev		= get_device_nr(0, drv_nr, 0);
	cmd.cmd		= 0xEC;		/* ATA identify */
	hd_command(&cmd);
	wait_hd_irq();
	io_insl(0x1F0, buf, 128);
	//size_t	i, k;
	static char	s[40];
	//u16	*hdinfo = (u16 *) buf;
	/*static struct	iden_info {
		size_t	idx;
		size_t	len;
		char	*dstr;
	} iinfo[] = {
		{10, 20, "HD SN"},
		{27, 40, "HD Model"}
	};
	for (k = 0; k < sizeof(iinfo) / sizeof(iinfo[0]); ++k) {
		char	*dstr = (char *) &hdinfo[iinfo[k].idx];
		for (i = 0; i < iinfo[k].len; ++i) {
			s[i] = *dstr++;
		}
		s[i] = 0;
		continue;
		printk("%s : %s", iinfo[k].dstr, s);
	}*/
	for (size_t i = 0; i < sizeof(buf); ++i) {
		printf("%02X ", buf[i]);
		if (i % 24 == 23)
			printf("\r\n");
	}
	printf("\r\n");
	memcpy(s, buf + 54, 40);
	s[20] = 0;
	printk("HD SN : %s", s);
	printk("HD Model : %s", s);
}


void	wait_hd_irq()
{
	int	recv_buf[2];
	size_t	recv_size = sizeof(recv_buf);
	tt_recvs(0, recv_buf, &recv_size);
}


void	hd_command(
		struct hd_cmd	*cmd)
{
	//printk("io_inb(0x1F7) = %02X", io_inb(0x1F7));
#ifndef	__GNUC__
	while (io_inb(0x1F7) & 0x80);	/* wait if busy */
#else
	__asm__ (	"movw	$0x1F7, %%dx\n"
			"1:"
			"inb	%%dx, %%al\n"
			"testb	$0x80, %%al\n"
			"jnz	1b\n" :: );
#endif
	io_outb(0, 0x3F6);
	io_outb(cmd->features, 0x1F1);
	io_outb(cmd->count, 0x1F2);
	io_outb(cmd->lba_lo, 0x1F3);
	io_outb(cmd->lba_md, 0x1F4);
	io_outb(cmd->lba_hi, 0x1F5);
	io_outb(cmd->dev, 0x1F6);
	io_outb(cmd->cmd, 0x1F7);
	
}


