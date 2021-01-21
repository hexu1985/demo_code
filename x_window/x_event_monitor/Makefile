
RM = rm -f
CXX = g++
CXXFLAGS = -Wall -g -DNDEBUG -std=c++11
INCLUDES = -I../../include
LDFLAGS = -lX11 -lXext -lXtst -lpthread
LDPATH =
VPATH = 

SOURCES = $(shell ls *.cpp)
PROGS = x_event_monitor

all: $(PROGS)
	@echo "PROGS = $(PROGS)" 

clean:
	$(RM) $(PROGS)

$(PROGS): $(SOURCES) $(LIB_SOURCES)
	$(CXX) -o $@ $(CXXFLAGS) $(INCLUDES) $^ $(LDFLAGS) $(LDPATH)
