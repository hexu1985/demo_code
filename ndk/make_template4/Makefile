# Makefile

RM = rm -f
CC = /opt/android-ndk-r14b/android-aarch64/bin/aarch64-linux-android-clang
CFLAGS = -Wall -g -fPIE 
INCLUDE = 
LDFLAGS = -pie
LDPATH = 

PROGS =	test1 test2 test3

.PHONY: all
all: $(PROGS)
	@echo "build OK!"

clean:
	@$(RM) $(PROGS) *.o
	@echo "clean OK!"

%.o:%.c
	$(CC) -o $@ -c $< $(CFLAGS) $(INCLUDE)

test1: test1.o
	$(CC) -o $@ $^ $(LDFLAGS) $(LDPATH)

test2: test2.o
	$(CC) -o $@ $^ $(LDFLAGS) $(LDPATH)

test3: test3.o
	$(CC) -o $@ $^ $(LDFLAGS) $(LDPATH)

