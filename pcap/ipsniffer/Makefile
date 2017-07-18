
RM = rm -f
CXX = g++
CXXFLAGS = -Wall -g
INCLUDES = -I../../lib/
LDFLAGS = -lpcap
LDPATH =
VPATH = ../../lib

SOURCES = $(shell ls *.cpp)
PROGS = $(SOURCES:%.cpp=%)

all: ipsniffer ipsniffer2
	@echo "PROGS = $(PROGS)" 

clean:
	$(RM) $(PROGS)

ipsniffer: ipsniffer.cpp 
	$(CXX) -o $@ $(CXXFLAGS) $(INCLUDES) $^ $(LDFLAGS) $(LDPATH)

ipsniffer2: ipsniffer2.cpp
	$(CXX) -o $@ $(CXXFLAGS) $(INCLUDES) $^ $(LDFLAGS) $(LDPATH)
