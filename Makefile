#######################
# Makefile for Matrix #
#######################

ARCH		=i386
CROSSC		=
MARCH		=
MCPU		=

GCC		=$(CROSSC)gcc
CC		=$(CROSSC)cc
AS		=$(CROSSC)as
LD		=$(CROSSC)ld
#SM		=$(CROSSC)nasm
OBJCOPY		=$(CROSSC)objcopy

MAKE		=make
SH		=sh
CAT		=cat
DD		=dd
RM		=rm -f
WC		=wc
SUDO		=sudo
SU		=$(SUDO) su
MOUNT		=$(SUDO) mount
LOSETUP		=$(SUDO) losetup
SUDODD		=$(SUDO) $(DD)
QEMU		=qemu-system-$(ARCH)
BOCHS		=bochsdbg

INCLUDE		=.
CC_OPTIZIME	=-Ofast
DEBUG_FLAG	=-g
CC_WARNNINGS	=-Wall -W -Wno-parentheses -Wno-main -Wno-long-long \
		 -Wno-comment -Wno-unused-parameter -Werror=type-limits \
		 -Werror=int-to-pointer-cast -Werror=int-conversion \
		 -Werror=pointer-to-int-cast -Werror=implicit-int \
		 -Werror=implicit-function-declaration
CC_DEFINES	=-D_ARCH=$(ARCH) -D_CROSSC=$(CROSSC) -D_CC=$(CC) \
		 -D_KERN_MAKE=1 -D_DEBUG=1
AS_FLAGS	=-a -I $(INCLUDE)
CC_FLAGS	=-c $(CC_OPTIZIME) $(DEBUG_FLAGS) $(CC_FORMATS) \
		 $(CC_WARNNINGS) $(CC_DEFINES) -I $(INCLUDE)
LD_FLAGS	=-N -e _start -Ttext 0 $(DEBUG_FLAG)

KERNEL_OBJS	=
BOOT_BIN	=boot/boot.bin
KERNEL_BIN	=kernel/kernel.bin
KERNEL_ELF	=kernel/kernel.elf
KERNEL		=$(KERNEL_BIN)
FDA_IMG		=boot.img

%.s.o : %.s
	$(AS) $(AS_FLAGS) -o $@ $< > /dev/null

%.c.o : %.c
	$(CC) $(CC_FLAGS) -o $@ $<

#%.asm.o : %.asm
#	$(SM) $(SM_FLAGS) -o $@ $<
#
#%.asm.bin : %.asm
#	$(SM) $(SM_BIN_FLAGS) -o $@ $<

default : run

all : boot.img

run : all
	$(QEMU) -m 16 -fda $(FDA_IMG) -boot a

$(FDA_IMG) : $(BOOT_BIN)
	$(CAT) $(BOOT_BIN) > $@

Image : $(KERNEL_BIN)
	$(CAT) $< > $@

$(BOOT_BIN) : boot/boot.s.o
	$(LD) $(LD_FLAGS) -o /tmp/tmp.out.$$ $<
	$(OBJCOPY) -O binary -R .note -R .comment -S /tmp/tmp.out.$$ $@
clean :
	$(RM) $(KERN_OBJS) $(BOOT_BIN) $(KERNEL_BIN) $(KERNEL_ELF) $(FDA_IMG) \
		*.o boot/*.o

