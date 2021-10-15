
RM = rm -f
CXX = g++
CXXFLAGS = -Wall -g -std=c++11
INCLUDES = -I../soxr/src
LDFLAGS = -lsoxr -lgomp
LDPATH = -L../soxr/build/src

SOURCES = $(shell ls *.cpp)
PROGS = $(subst .cpp,,$(SOURCES))
#PROGS = $(SOURCES:%.cpp=%)

all: $(PROGS)
	@echo "PROGS = $(PROGS)" 

clean:
	$(RM) $(PROGS)

%: %.cpp
	$(CXX) -o $@ $(CXXFLAGS) $(INCLUDES) $^ $(LDFLAGS) $(LDPATH)
