# Makefile

RM = rm -f
CXX = g++
CXXFLAGS = -Wall -g $(shell libnet-config --defines)
#CXXFLAGS = -Wall -g -DNDEBUG -D_BSD_SOURCE -D__BSD_SOURCE -D__FAVOR_BSD -DHAVE_NET_ETHERNET_H
INCLUDE = 
LDFLAGS = $(shell libnet-config --libs) -lpcap #-lpthread -lrt
#LDFLAGS = -lnet -lpcap #-lpthread -lrt
LDPATH = 

PROGS =	httpredirect

.PHONY: all
all: $(PROGS)
	@echo "build OK!"

clean:
	@$(RM) $(PROGS) *.o
	echo "clean OK!"

%.o:%.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS) $(INCLUDE)

httpredirect: httpget.o httpredirect.o sendtcpresp.o 
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)

