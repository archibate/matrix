#pragma once


#define	FS_DAE	4

#define	FS_SCNR_open	1
#define	FS_SCNR_read	2
#define	FS_SCNR_write	3
#define	FS_SCNR_close	4
#define	FS_SCNR_seek	5

#define	get_device_nr(lba, drv_nr, lba_hi) \
	(((lba) << 6) | ((drv_nr) << 4) | (((lba_hi) & 0xF) | 0xA0))

typedef	size_t	lba_t;
typedef	size_t	drv_nr_t;
typedef	size_t	dev_nr_t;

struct	hd_cmd {
	u8	features;
	u8	count;
	u8	lba_lo;
	u8	lba_md;
	u8	lba_hi;
	u8	dev;
	u8	com;
	u8	unused;
};

struct	drive {
	drv_nr_t	nr;
	lba_t		sects;
	u8		buf[512];
	u8		supports;
	char		serial[20];
	char		model[40];
};


void	init_hd();
void	fs_daemon();
void	hd_drive_read(
		struct drive	*drv,
		lba_t	lba,
		lba_t	sects);
void	open_hd_drive(
		struct drive	*drv,
		drv_nr_t	drv_nr);
void	hd_command(
		struct hd_cmd	*cmd);
void	wait_hd_irq();


