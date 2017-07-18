
RM = rm -f
CXX = g++
CXXFLAGS = -Wall -g
INCLUDES = -I../../lib/
LDFLAGS = -lpcap
LDPATH =
VPATH = ../../lib

PROGS = wget2

all: $(PROGS)
	@echo "PROGS = $(PROGS)" 

clean:
	$(RM) $(PROGS)

wget2: wget2.cpp httpresp.cpp http_parser.cpp
	$(CXX) -o $@ $(CXXFLAGS) $(INCLUDES) $^ $(LDFLAGS) $(LDPATH)

