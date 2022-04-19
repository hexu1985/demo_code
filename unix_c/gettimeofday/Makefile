
RM = rm -f
CC = g++
CFLAGS = -Wall -g
INCLUDES = 
LDFLAGS =
LDPATH =

SOURCES = $(shell ls *.c)
PROGS = $(subst .c,,$(SOURCES))
#PROGS = $(SOURCES:%.c=%)

all: $(PROGS)
	@echo "PROGS = $(PROGS)" 

clean:
	$(RM) $(PROGS)

%: %.c
	$(CC) -o $@ $(CFLAGS) $(INCLUDES) $^ $(LDFLAGS) $(LDPATH)
