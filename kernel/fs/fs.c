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
	pid_t	sender = 0;
	static int	recv_buf[1];
	size_t	recv_size;
	extern struct task	*task_ready;
	//extern struct task	*tasks;
	static struct drive	drv_hda;

	init_hd();
	strcpy(task_ready->name, "FS");
	printk("Devices count in BIOS Data Area : %d", * (u8 *) 0x475);
	open_hd_drive(&drv_hda, 0);	/* /dev/hda */
	hd_drive_read(&drv_hda, 0, 1);
	/*printk("Data in /dev/hda :");
	for (int i = 0; i < 512; ++i) {
		printf("%02X ", drv_hda.buf[i]);
		if (i % (TTY_XS / 3) == (TTY_XS / 3) - 1)
			printf("\r\n");
	}
	printf("\r\n");*/
	//io_hlt();

	for (;;) {
		memset(recv_buf, 0, recv_size = sizeof(recv_buf));
		recv_buf[0] = 9;
		sender = tt_recvs(0, recv_buf, &recv_size);
		//sender = sender + 1 - 1;

		switch (recv_buf[0]) {
		case FS_SCNR_open:
			continue;
		default:
			printk("System Call Error : %d is not an index of FS SysCall",
					recv_buf[0]);
			panic("sender = %d", sender);
			continue;
		}
	}

}


void	hd_drive_read(
		struct drive	*drv,
		lba_t	lba,
		lba_t	sects)
{
	struct hd_cmd	cmd;
	cmd.features	= 0;
	cmd.count	= sects;
	cmd.lba_lo	= (u8) lba;
	cmd.lba_md	= (u8) (lba >> 8);
	cmd.lba_hi	= (u8) (lba >> 16);
	cmd.dev		= get_device_nr(1, drv->nr, (lba >> 24) & 0xF);
	cmd.com		= 0x20;	/* Read */
	hd_command(&cmd);
	u8	*buf = drv->buf;
	while (sects--) {
		//wait_hd_irq();
		io_insl(0x1F0, buf, 128);
	}
}


void	hd_drive_write(
		struct drive	*drv,
		lba_t	lba,
		lba_t	sects)
{
	struct hd_cmd	cmd;
	cmd.features	= 0;
	cmd.count	= sects;
	cmd.lba_lo	= (u8) lba;
	cmd.lba_md	= (u8) (lba >> 8);
	cmd.lba_hi	= (u8) (lba >> 16);
	cmd.dev		= get_device_nr(1, drv->nr, (lba >> 24) & 0xF);
	cmd.com		= 0x30;	/* Read */
	hd_command(&cmd);
	u8	*buf = drv->buf;
	while (sects--) {
		while (!(io_inb(0x1F7) & 0x08));
		io_insl(0x1F0, buf, 128);
		//wait_hd_irq();
	}
}


void	open_hd_drive(
		struct drive	*drv,
		drv_nr_t	drv_nr)
{
	memset(drv, 0, sizeof(*drv));
	drv->nr = drv_nr;
	static struct hd_cmd	cmd;
	memset(&cmd, 0, sizeof(cmd));
#if	0
	cmd.dev		= get_device_nr(0, drv_nr, 0);
	cmd.cmd		= 0x30;		/* Write */
	cmd.count	= 1;
	hd_command(&cmd);
	//wait_hd_irq();
	while (!(io_inb(0x1F7) & 0x08));
	io_outsl(0x1F0, buf, 128);
	for (size_t i = 0; i < sizeof(buf) / 16; ++i) {
		printf("%02X ", buf[i]);
		if (i % 24 == 23)
			printf("\r\n");
	}
	printf("\r\n");
	panic("sfadasd");
#endif

	cmd.dev		= get_device_nr(0, drv_nr, 0);
	cmd.com		= 0xEC;		/* ATA identify */
	hd_command(&cmd);
	/*******************\
	|* Hello, Comment! *|
	while (!(io_inb(0x1F7) & 0x08));
	io_outsl(0x1F0, buf, 128);
	\*******************/
	//wait_hd_irq();
	io_insl(0x1F0, drv->buf, 128);
	//size_t	i, k;
	char	*s;
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
	/*for (size_t i = 0; i < sizeof(buf); ++i) {
		printf("%02X ", buf[i]);
		if (i % 24 == 23)
			printf("\r\n");
	}
	printf("\r\n");*/
	size_t	i;
	char	*p;
	u16	*idbuf = (u16 *) drv->buf;
	for (i = 0, p = (char *) (idbuf + 10), s = drv->serial; i < 20; i += 2) {
		s[i + 1] = *p++;
		s[i] = *p++;
	}
	s[20] = 0;
	printk("HD SN : %s", s);
	for (i = 0, p = (char *) (idbuf + 27), s = drv->model; i < 40; i += 2) {
		s[i + 1] = *p++;
		s[i] = *p++;
	}
	s[40] = 0;
	printk("HD Model : %s", s);
	printk("LBA supported : %s",
			idbuf[49] & 0x0200 ? "Yes" : "No");
	drv->supports = ((idbuf[49] & 0x0200) | (idbuf[83] & 0x0400)) >> 8;
	printk("LBA48 Supported : %s",
			idbuf[83] & 0x0400 ? "Yes" : "No");
	drv->sects = ((u32) idbuf[61] << 16) + idbuf[60];
	printk("Disk Size : %dMB", drv->sects * 512 / 1000000);
	//panic("sfadasd");
}


void	wait_hd_irq()
{
	int	recv_buf[2];
	size_t	recv_size = sizeof(recv_buf);
	tt_recvs(TT_DAE, recv_buf, &recv_size);
}


void	hd_command(
		struct hd_cmd	*cmd)
{
	//printk("io_inb(0x1F7) = %02X", io_inb(0x1F7));
#ifndef	__GNUC__	/* I could not say any thing about the 'best' complier */
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
	io_outb(cmd->com, 0x1F7);
	
}


