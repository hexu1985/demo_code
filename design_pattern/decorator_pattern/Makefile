
RM = rm -f
CXX = g++
CXXFLAGS = -Wall -g -DNDEBUG 
INCLUDES = 
LDFLAGS = 
LDPATH =
VPATH = 

HEADERS =  $(shell ls *.h)
SOURCES = $(shell ls *.cpp)
PROGS = starbuzz_coffee

all: $(PROGS)
	@echo "PROGS = $(PROGS)" 

clean:
	$(RM) $(PROGS)

$(PROGS): $(SOURCES) $(HEADERS)
	$(CXX) -o $@ $(CXXFLAGS) $(INCLUDES) $(SOURCES) $(LDFLAGS) $(LDPATH)
