
RM = rm -f
CXX = g++
CXXFLAGS = -Wall -g
INCLUDES = -I/home/hexu/local/include
LDFLAGS = -lgtest -lpthread
LDPATH = -L/home/hexu/local/lib
VPATH = 

SOURCES = $(shell ls *.cpp)
PROGS = sample

all: $(PROGS)
	@echo "PROGS = $(PROGS)" 

clean:
	$(RM) $(PROGS)

$(PROGS): $(SOURCES) $(LIB_SOURCES)
	$(CXX) -o $@ $(CXXFLAGS) $(INCLUDES) $^ $(LDFLAGS) $(LDPATH)
