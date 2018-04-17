# Makefile

RM = rm -f
CXX = g++
CXXFLAGS = -Wall -g
INCLUDE = 
LDFLAGS = 
LDPATH = 

OBJS = error.o wrapsock.o wraplib.o sock_ntop.o
PROGS =	udp_send udp_recv

.PHONY: all
all: $(PROGS)
	@echo "build OK!"

clean:
	@$(RM) $(PROGS) *.o
	@echo "clean OK!"

%.o:%.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS) $(INCLUDE)

udp_send: udp_send.o $(OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)

udp_recv: udp_recv.o $(OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)

