 include	../../Makefile.header

LIB_OBJS	=memory.c.o string.c.o vsprintf.c.o
LIB		=lib.a

target : $(LIB)

$(LIB) : $(LIB_OBJS)
	$(AR) cqs $@ $(LIB_OBJS)

clean :
	$(RM) $(LIB_OBJS) $(LIB)

