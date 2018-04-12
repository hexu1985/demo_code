# Makefile

RM = rm -f
CC = gcc
CFLAGS = -Wall -g
INCLUDE = 
LDFLAGS = 
LDPATH = 

OBJS = open_dev.o set_speed.o set_parity.o
PROGS =	tty_read tty_read2 

.PHONY: all
all: $(PROGS)
	@echo "build OK!"

clean:
	@$(RM) $(PROGS) *.o
	@echo "clean OK!"

%.o:%.c
	$(CC) -o $@ -c $< $(CFLAGS) $(INCLUDE)

tty_read: tty_read.o $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS) $(LDPATH)

tty_read2: tty_read2.o $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS) $(LDPATH)


