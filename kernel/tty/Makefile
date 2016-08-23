 include	../../Makefile.header

TTY_OBJS	=ttyio.c.o
TTY		=tty.a

target : $(TTY)

$(TTY) : $(TTY_OBJS)
	$(AR) cqs $@ $(TTY_OBJS)

clean :
	$(RM) $(TTY_OBJS) $(TTY)

