#pragma once


#define	FS_DAE	4

#define	FS_SCNR_dev_open	1

#define	get_device_nr(lba, drv_nr, lba_hi) \
	(((lba) << 6) | ((drv_nr) << 4) | (((lba_hi) & 0xF) | 0xA0))

struct	hd_cmd {
	u8	features;
	u8	count;
	u8	lba_lo;
	u8	lba_md;
	u8	lba_hi;
	u8	dev;
	u8	cmd;
};


void	init_hd();
void	fs_daemon();
void	hd_drive_identify(
		int	drv_nr);
void	hd_command(
		struct hd_cmd	*cmd);
void	wait_hd_irq();


