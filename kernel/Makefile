 include	../Makefile.header

KERNEL_OBJS	=start.s.o
KERNEL_ELF	=kernel.elf
KERNEL_BIN	=kernel.bin
KERNEL		=$(KERNEL_BIN)

target : $(KERNEL_BIN)

$(KERNEL_BIN) : $(KERNEL_ELF)
	$(OBJCOPY) -O binary -R .note -R .commit -S $< $@

$(KERNEL_ELF) : $(KERNEL_OBJS)
	$(LD) $(LD_FLAGS) -o $@ $(KERNEL_OBJS)

clean :
	$(RM) $(KERNEL_OBJS) $(KERNEL_ELF) $(KERNEL_BIN)

