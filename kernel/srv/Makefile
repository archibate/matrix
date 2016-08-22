 include	../../Makefile.header

SRV_OBJS	=isr.s.o
SRV		=srv.a

target : $(SRV)

$(SRV) : $(SRV_OBJS)
	$(AR) cqs $@ $(SRV_OBJS)

clean :
	$(RM) $(SRV_OBJS) $(SRV)

