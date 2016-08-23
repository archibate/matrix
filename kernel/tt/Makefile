 include	../../Makefile.header

TT_OBJS		=tt.c.o
TT		=tt.a

target : $(TT)

$(TT) : $(TT_OBJS)
	$(AR) cqs $@ $(TT_OBJS)

clean :
	$(RM) $(TT_OBJS) $(TT)

