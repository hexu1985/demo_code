# Makefile

LEX = lex
RMR = rm -rf
RM = rm -f
CC = gcc

VPATH = ./gen-cpp
CFLAGS = -Wall -g -DDEBUG 
INCLUDE = 
LDFLAGS = -lfl
LDPATH = 

OBJS = echo_constants.o echo_types.o EchoTest.o

PROGS = example1

.PHONY: all
all: $(PROGS)
	@echo "build OK!"

.PHONY: clean
clean:
	$(RM) $(PROGS) *.o *.obj *.exe
	@echo "clean OK!"

.PHONY: lex
lex: ch102.l
	$(LEX) $<

.PHONY: distclean
distclean: lex-clean clean 

.PHONY: lex-clean
lex-clean:
	rm lex.yy.c

lex.yy.c: ch102.l
	$(LEX) $<

%.o:%.c
	$(CC) -o $@ -c $< $(CFLAGS) $(INCLUDE)

example1: lex.yy.o
	$(CC) -o $@ $^ $(LDFLAGS) $(LDPATH)

