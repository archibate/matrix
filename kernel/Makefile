 include	../Makefile.header

LD_FLAGS	+=-Ttext 0x8000
INIT		=init/init.a
KERNEL_OBJS	=start.s.o $(INIT)
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

clean :
	$(RM) $(KERNEL_OBJS) $(KERNEL_ELF) $(KERNEL_BIN) $(KERNEL_MAP)
	$(MAKE) -r clean -C init/

