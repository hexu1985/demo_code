
RM = rm -f
CXX = g++
CXXFLAGS = -Wall -g
INCLUDES = -I../sqlite3
LDFLAGS = ../sqlite3/libsqlite-see.a -lpthread -ldl
LDPATH = 

SOURCES = $(shell ls *.cpp)
PROGS = $(SOURCES:%.cpp=%)

all: $(PROGS)
	@echo "PROGS = $(PROGS)" 

clean:
	$(RM) $(PROGS) *.db

%: %.cpp
	$(CXX) -o $@ $(CXXFLAGS) $(INCLUDES) $^ $(LDFLAGS) $(LDPATH)
