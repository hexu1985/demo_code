
RM = rm -f
CXX = g++
CXXFLAGS = -Wall -g -DNDEBUG `libnet-config --defines`
INCLUDES = -I../../include
LDFLAGS = -lpcap `libnet-config --libs` #-lnet 
LDPATH =
VPATH = 

SOURCES = $(shell ls *.cpp)
PROGS = httpredirect

all: $(PROGS)
	@echo "PROGS = $(PROGS)" 

clean:
	$(RM) $(PROGS)

$(PROGS): $(SOURCES) $(LIB_SOURCES)
	$(CXX) -o $@ $(CXXFLAGS) $(INCLUDES) $^ $(LDFLAGS) $(LDPATH)
