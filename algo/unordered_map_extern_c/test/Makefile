# Makefile

RM = rm -f
CC = gcc
CFLAGS = -Wall -g -std=c99 -DTEST_DELETE
INCLUDE = -I../lib
LDFLAGS = ../lib/libalgo.a -lstdc++
LDPATH = 

PROGS =	test

.PHONY: all
all: $(PROGS)
	@echo "build OK!"

clean:
	@$(RM) $(PROGS) *.o
	@echo "clean OK!"

%.o:%.c
	$(CC) -o $@ -c $< $(CFLAGS) $(INCLUDE)

test: test.o
	$(CC) -o $@ $^ $(LDFLAGS) $(LDPATH)

