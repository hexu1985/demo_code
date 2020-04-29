
RM = rm -f
CXX = g++
CXXFLAGS = -Wall -g
INCLUDES = -I$(HOME)/local/include
LDFLAGS = -lglog -lgflags -lpthread
LDPATH = -L$(HOME)/local/lib

SOURCES = $(shell ls *.cpp)
PROGS = $(SOURCES:%.cpp=%)

all: $(PROGS)
	@echo "PROGS = $(PROGS)" 

clean:
	$(RM) $(PROGS) log/*

%: %.cpp
	$(CXX) -o $@ $(CXXFLAGS) $(INCLUDES) $^ $(LDFLAGS) $(LDPATH)
