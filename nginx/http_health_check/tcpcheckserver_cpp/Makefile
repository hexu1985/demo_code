# Makefile

RM = rm -f
CXX = g++
CXXFLAGS = -Wall -g -std=c++11 -DHAVE_EPOLL
INCLUDE = -I../lib
LDFLAGS = -lpthread -lrt
LDPATH = 

PROGS =	tcpechoserver tcpcheckserver

.PHONY: all
all: $(PROGS)
	@echo "build OK!"

clean:
	@$(RM) $(PROGS) *.o
	@echo "clean OK!"

%.o:%.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS) $(INCLUDE)

tcpechoserver: tcpechoserver.o tcpserver.o wrapunix.o writen.o error.o wrapsock.o tcp_listen.o sock_ntop.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)

tcpcheckserver: tcpcheckserver.o tcpserver.o wrapunix.o error.o wrapsock.o tcp_listen.o sock_ntop.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)


