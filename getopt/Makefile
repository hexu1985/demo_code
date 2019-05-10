
RM = rm -f
CC = gcc
CFLAGS = -Wall -g
INCLUDES = -I.getopt/
LDFLAGS =
LDPATH =

SOURCES = $(shell ls *.c)
PROGS = $(SOURCES:%.c=%)

all: $(PROGS)
	@echo "PROGS = $(PROGS)" 

clean:
	$(RM) $(PROGS)

%: %.c
	$(CC) -o $@ $(CFLAGS) $(INCLUDES) $^ $(LDFLAGS) $(LDPATH)
