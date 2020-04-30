
RM = rm -f
CXX = g++
CXXFLAGS = -Wall -g -std=c++11
INCLUDES = -I$(HOME)/local/include
LDFLAGS = -lgflags -lpthread
LDPATH = -L$(HOME)/local/lib
VPATH = 

SOURCES = $(shell ls *.cpp)
PROGS = gflags_declare_test

all: $(PROGS)
	@echo "PROGS = $(PROGS)" 

clean:
	$(RM) $(PROGS)

$(PROGS): $(SOURCES) $(LIB_SOURCES)
	$(CXX) -o $@ $(CXXFLAGS) $(INCLUDES) $^ $(LDFLAGS) $(LDPATH)
