
RM = rm -f
CXX = g++
CXXFLAGS = -Wall -g
INCLUDES = -I./SQLiteCpp/include
LDFLAGS = -lsqlite3
LDPATH = 

SOURCES = $(shell ls *.cpp)
PROGS = $(SOURCES:%.cpp=%)

all: $(PROGS)
	@echo "PROGS = $(PROGS)" 

clean:
	$(RM) $(PROGS) *.db

%: %.cpp
	$(CXX) -o $@ $(CXXFLAGS) $(INCLUDES) $^ $(LDFLAGS) $(LDPATH)
