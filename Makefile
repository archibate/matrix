#######################
# Makefile for Matrix #
#######################

 include	Makefile.header


BOOT_BIN	=boot/boot.bin
KERNEL_BIN	=kernel/kernel.bin
KERNEL_ELF	=kernel/kernel.elf
KERNEL		=$(KERNEL_BIN)
FDA_IMG		=boot.img


default : run

all : boot.img

run : all
	$(QEMU) -m 16 -fda $(FDA_IMG) -boot a

$(FDA_IMG) : $(BOOT_BIN) $(KERNEL_BIN)
	$(CAT) $(BOOT_BIN) $(KERNEL_BIN) > $@

#Image : $(KERNEL_BIN)
#	$(CAT) $< > $@

$(BOOT_BIN) : boot/*
	$(MAKE) -r target -C boot/

$(KERNEL_BIN) : kernel/*
	$(MAKE) -r target -C kernel/

clean :
	$(RM) $(FDA_IMG)
	$(MAKE) -r clean -C boot/

