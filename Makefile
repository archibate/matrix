#######################
# Makefile for Matrix #
#######################

 include	Makefile.header


KERNEL_OBJS	=
BOOT_BIN	=boot/boot.bin
KERNEL_BIN	=kernel/kernel.bin
KERNEL_ELF	=kernel/kernel.elf
KERNEL		=$(KERNEL_BIN)
FDA_IMG		=boot.img


default : run

all : boot.img

run : all
	$(QEMU) -m 16 -fda $(FDA_IMG) -boot a

$(FDA_IMG) : $(BOOT_BIN)
	$(CAT) $(BOOT_BIN) > $@

#Image : $(KERNEL_BIN)
#	$(CAT) $< > $@

$(BOOT_BIN) : boot/boot.s.o
	$(MAKE) -r target -C boot/

clean :
	$(RM) $(KERN_OBJS) $(BOOT_BIN) $(KERNEL_BIN) $(KERNEL_ELF) $(FDA_IMG)
	$(MAKE) -r clean -C boot/

