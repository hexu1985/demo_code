
RM = rm -f
CXX = g++
CXXFLAGS = -Wall -g
INCLUDES = -I../../lib/
LDFLAGS = -lpcap
LDPATH =
VPATH = ../../lib

SOURCES = $(shell ls *.cpp)
PROGS = $(SOURCES:%.cpp=%)

all: httpsniffer httpsniffer2
	@echo "PROGS = $(PROGS)" 

clean:
	$(RM) $(PROGS)

httpsniffer: httpsniffer.cpp httpget.cpp
	$(CXX) -o $@ $(CXXFLAGS) $(INCLUDES) $^ $(LDFLAGS) $(LDPATH)

httpsniffer2: httpsniffer2.cpp httpget.cpp
	$(CXX) -o $@ $(CXXFLAGS) $(INCLUDES) $^ $(LDFLAGS) $(LDPATH)
