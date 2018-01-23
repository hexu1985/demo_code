
RM = rm -f
CXX = g++
CXXFLAGS = -Wall -g
INCLUDES = 
LDFLAGS = -lglog
LDPATH =

SOURCES = $(shell ls *.cpp)
PROGS = $(SOURCES:%.cpp=%)

all: $(PROGS)
	@echo "PROGS = $(PROGS)" 

clean:
	$(RM) $(PROGS) log/*

%: %.cpp
	$(CXX) -o $@ $(CXXFLAGS) $(INCLUDES) $^ $(LDFLAGS) $(LDPATH)
