 include	../Makefile.header

LD_FLAGS	+=-Ttext 0x8000
INIT		=init/init.a
SRV		=srv/srv.a
TT		=tt/tt.a
MM		=mm/mm.a
TTY		=tty/tty.a
LIB		=lib/lib.a
FS		=fs/fs.a
KERNEL_OBJS	=start.s.o $(INIT) $(SRV) $(TT) $(MM) $(TTY) $(LIB) $(FS)
KERNEL_ELF	=kernel.elf
KERNEL_BIN	=kernel.bin
KERNEL_MAP	=kernel.map
KERNEL		=$(KERNEL_BIN)

target : $(KERNEL_BIN)

$(KERNEL_BIN) : $(KERNEL_ELF)
	$(OBJCOPY) -O binary -R .note -R .commit -S $< $@

$(KERNEL_ELF) : $(KERNEL_OBJS)
	$(LD) $(LD_FLAGS) -o $@ -Map $(KERNEL_MAP) $(KERNEL_OBJS)

$(INIT) : $(wildcard init/*)
	$(MAKE) -r target -C init/

$(SRV) : $(wildcard srv/*)
	$(MAKE) -r target -C srv/

$(TT) : $(wildcard tt/*)
	$(MAKE) -r target -C tt/

$(MM) : $(wildcard mm/*)
	$(MAKE) -r target -C mm/

$(TTY) : $(wildcard tty/*)
	$(MAKE) -r target -C tty/

$(LIB) : $(wildcard lib/*)
	$(MAKE) -r target -C lib/

$(FS) : $(wildcard fs/*)
	$(MAKE) -r target -C fs/

clean :
	$(RM) $(KERNEL_OBJS) $(KERNEL_ELF) $(KERNEL_BIN) $(KERNEL_MAP)
	$(MAKE) -r clean -C init/

