
RM = rm -f
CXX = g++
CXXFLAGS = -Wall -g
INCLUDES = -I./SQLiteCpp/include
LDFLAGS = -lSQLiteCpp -lsqlite3
LDPATH = -L.

SOURCES = $(shell ls *.cpp)
PROGS = $(SOURCES:%.cpp=%)

all: $(PROGS)
	@echo "PROGS = $(PROGS)" 

clean:
	$(RM) $(PROGS)

%: %.cpp
	$(CXX) -o $@ $(CXXFLAGS) $(INCLUDES) $^ $(LDFLAGS) $(LDPATH)
