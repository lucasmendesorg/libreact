#
# Observables for C
#	(c) 2020 Lucas Mendes <lucas AT lucasmendes.org>
#

     CC	= cc
  STRIP	= strip
     
 CFLAGS	= -O3 -Wall -funroll-loops -I.
#CFLAGS	+= -fno-asynchronous-unwind-tables -fno-dwarf2-cfi-asm -S
 
LDFLAGS	=

   OBJS	= main.o debug.o event.o observable.o observer.o

   AOUT	= react

all: $(OBJS)
	$(CC) -o $(AOUT) $(OBJS) $(LDFLAGS)
	$(STRIP) $(AOUT)

debug: $(OBJS)
	$(CC) -o $(AOUT) $(OBJS) $(LDFLAGS)

debug: CFLAGS += -DDEBUG

clean:
	$(RM) $(OBJS) $(AOUT)
