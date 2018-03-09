
RM = rm -f
CC = g++
CFLAGS = -Wall -g
INCLUDES = -I./include 
LDFLAGS = -lzmq -pthread
LDPATH =

SOURCES = $(shell ls *.c)
PROGS = $(SOURCES:%.c=%)

all: $(PROGS)
	@echo "PROGS = $(PROGS)" 

clean:
	$(RM) $(PROGS)

%: %.c
	$(CC) -o $@ $(CFLAGS) $(INCLUDES) $^ $(LDFLAGS) $(LDPATH)

CZMQ3_INCLUDES = -I$(HOME)/third-party/czmq-3.0.2/include 
CZMQ3_LDPATH = -L$(HOME)/third-party/czmq-3.0.2/src/.libs
CZMQ3_LDFLAGS = -Wl,-R$(HOME)/third-party/czmq-3.0.2/src/.libs -Wl,--enable-new-dtags

lbbroker2: lbbroker2.c
	$(CC) -o $@ $(CFLAGS) $(INCLUDES) $(CZMQ3_INCLUDES) $^ -lczmq $(LDFLAGS) $(LDPATH) $(CZMQ3_LDFLAGS) $(CZMQ3_LDPATH) 

lbbroker3: lbbroker3.c
	$(CC) -o $@ $(CFLAGS) $(INCLUDES) $(CZMQ3_INCLUDES) $^ -lczmq $(LDFLAGS) $(LDPATH) $(CZMQ3_LDFLAGS) $(CZMQ3_LDPATH) 
