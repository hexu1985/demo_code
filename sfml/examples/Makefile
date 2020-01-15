
RM = rm -f
CXX = g++
CXXFLAGS = -Wall -g -std=c++11
INCLUDES = 
LDFLAGS = -lsfml-audio -lpthread
LDPATH =

SOURCES = $(shell ls *.cpp)
PROGS = $(SOURCES:%.cpp=%)

all: $(PROGS)
	@echo "PROGS = $(PROGS)" 

clean:
	$(RM) $(PROGS) log/*

%: %.cpp
	$(CXX) -o $@ $(CXXFLAGS) $(INCLUDES) $^ $(LDFLAGS) $(LDPATH)
