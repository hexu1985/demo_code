
RM = rm -f
CXX = g++
CXXFLAGS = -Wall -g
INCLUDES = 
LDFLAGS = -lgtest
LDPATH =
VPATH = 

SOURCES = $(shell ls *.cpp)
PROGS = gtest_test

all: $(PROGS)
	@echo "PROGS = $(PROGS)" 

clean:
	$(RM) $(PROGS)

$(PROGS): $(SOURCES) $(LIB_SOURCES)
	$(CXX) -o $@ $(CXXFLAGS) $(INCLUDES) $^ $(LDFLAGS) $(LDPATH)
