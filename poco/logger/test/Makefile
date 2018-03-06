
RM = rm -f
CXX = g++
CXXFLAGS = -Wall -g #-static
INCLUDES = 
LDFLAGS = -lPocoFoundation
LDPATH =
VPATH = 

SOURCES = $(shell ls *.cpp)
PROGS = test_logger

all: $(PROGS)
	@echo "PROGS = $(PROGS)" 

clean:
	$(RM) $(PROGS)

$(PROGS): $(SOURCES) $(LIB_SOURCES)
	$(CXX) -o $@ $(CXXFLAGS) $(INCLUDES) $^ $(LDFLAGS) $(LDPATH)
