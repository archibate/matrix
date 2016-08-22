 include	../../Makefile.header

INIT_OBJS	=init.c.o desc.c.o
INIT		=init.a

target : $(INIT)

$(INIT) : $(INIT_OBJS)
	$(AR) cqs $@ $(INIT_OBJS)

clean :
	$(RM) $(INIT_OBJS) $(INIT)

