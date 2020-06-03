#
# LibReact -- Reactive Programming in C
#

     CC	= cc
 CFLAGS	= -Wall
LDFLAGS	=

   OBJS	= main.o
   AOUT	= react

all: $(OBJS)
	$(CC) -o $(AOUT) $(OBJS) $(LDFLAGS)

clean:
	$(RM) $(OBJS) $(AOUT)
