# Makefile

RM = rm -f
CXX = g++
CXXFLAGS = -Wall -g -std=c++11 -DHAVE_EPOLL
INCLUDE = -I ../../lib
LDFLAGS = -lboost_program_options -lpthread -lrt
LDPATH =

PROGS =	udp_stree_client

.PHONY: all
all: $(PROGS)
	@echo "build OK!"

clean:
	@$(RM) $(PROGS) *.o
	@echo "clean OK!"

%.o:%.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS) $(INCLUDE)

udp_stree_client: wrapsock.o udp_connect.o error.o prog_opts_util.o statistics.o main.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)

