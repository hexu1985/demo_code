# Makefile

LEX = flex
RMR = rm -rf
RM = rm -f
CC = gcc

VPATH = 
CFLAGS = -Wall -g -DDEBUG 
INCLUDE = 
LDFLAGS = -lfl
LDPATH = 

PROGS = ch102.exe

.PHONY: all
all: $(PROGS)
	@echo "build OK!"

.PHONY: clean
clean:
	$(RM) $(PROGS) *.o *.obj *.exe *.l.c
	@echo "clean OK!"

%.l.c:%.l
	$(LEX) -o $@ $<

ch102.exe: ch102.l.c
	$(CC) -o $@ $^ $(LDFLAGS) $(LDPATH)

