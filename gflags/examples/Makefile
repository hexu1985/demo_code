
RM = rm -f
CXX = g++
CXXFLAGS = -Wall -g
INCLUDES = -I$(HOME)/local/include
LDFLAGS = -lgflags -lpthread
LDPATH = -L$(HOME)/local/lib

SOURCES = $(shell ls *.cpp)
PROGS = $(SOURCES:%.cpp=%)

all: $(PROGS)
	@echo "PROGS = $(PROGS)" 

clean:
	$(RM) $(PROGS)

%: %.cpp
	$(CXX) -o $@ $(CXXFLAGS) $(INCLUDES) $^ $(LDFLAGS) $(LDPATH)
