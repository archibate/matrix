 include	../../Makefile.header

FS_OBJS		=fs.c.o
FS		=fs.a

target : $(FS)

$(FS) : $(FS_OBJS)
	$(AR) cqs $@ $(FS_OBJS)

clean :
	$(RM) $(FS_OBJS) $(FS)

