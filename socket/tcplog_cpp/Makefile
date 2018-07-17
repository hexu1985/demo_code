# Makefile

RM = rm -f
CXX = g++
CXXFLAGS = -Wall -g -std=c++11 -DIPV6
INCLUDE = -I..
LDFLAGS = -lpthread
LDPATH = 
VPATH = ..

PROGS =	tcplog_server

.PHONY: all
all: $(PROGS)
	@echo "build OK!"

clean:
	@$(RM) $(PROGS) *.o
	@echo "clean OK!"

%.o:%.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS) $(INCLUDE)

tcplog_server: tcplog_server.o tcp_listen.o sock_get_port.o sock_ntop_host.o sock_ntop.o wrapsock.o error.o utc_to_string.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)

