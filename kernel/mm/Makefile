 include	../../Makefile.header

MM_OBJS		=mm.c.o pg.c.o
MM		=mm.a

target : $(MM)

$(MM) : $(MM_OBJS)
	$(AR) cqs $@ $(MM_OBJS)

clean :
	$(RM) $(MM_OBJS) $(MM)

