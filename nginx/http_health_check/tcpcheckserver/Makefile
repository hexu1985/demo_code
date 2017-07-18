
RM = rm -f
CC = gcc
CFLAGS = -Wall -g 
INCLUDES = -I../../include
LDFLAGS = 
LDPATH =
VPATH = 

SOURCES = $(shell ls *.c)
PROGS = tcpcheckserver

all: $(PROGS)
	@echo "PROGS = $(PROGS)" 

clean:
	$(RM) $(PROGS)

$(PROGS): $(SOURCES) $(LIB_SOURCES)
	$(CC) -o $@ $(CFLAGS) $(INCLUDES) $^ $(LDFLAGS) $(LDPATH)
