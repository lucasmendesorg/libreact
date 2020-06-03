#
# LibReact -- Reactive Programming in C
#

     CC	= cc
 CFLAGS	= -O3 -Wall -funroll-loops -I.
LDFLAGS	=

   OBJS	= main.o debug.o event.o observable.o observer.o
   AOUT	= react

all: $(OBJS)
	$(CC) -o $(AOUT) $(OBJS) $(LDFLAGS)

clean:
	$(RM) $(OBJS) $(AOUT)
