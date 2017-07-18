# Makefile

RM = rm -f
CC = gcc
CFLAGS = -Wall -g
INCLUDE = 
LDFLAGS = 
LDPATH = 

PROGS =	nslookup_v4

.PHONY: all
all: $(PROGS)
	@echo "build OK!"

clean:
	@$(RM) $(PROGS) *.o
	@echo "clean OK!"

%.o:%.c
	$(CC) -o $@ -c $< $(CFLAGS) $(INCLUDE)

nslookup_v4: nslookup_v4.o error.o sock_ntop.o
	$(CC) -o $@ $^ $(LDFLAGS) $(LDPATH)


