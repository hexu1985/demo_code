
RM = rm -f
CXX = g++
CXXFLAGS = -Wall -g -std=c++11
INCLUDES = 
LDFLAGS = -lXrandr -lXinerama -lXext -lX11 -lpthread
LDPATH =

SOURCES = $(shell ls *.cpp)
PROGS = x_monitor_info_query

all: $(PROGS)
	@echo "PROGS = $(PROGS)" 

clean:
	$(RM) $(PROGS) *.o

%.o:%.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS) $(INCLUDE)

x_monitor_info_query: x_monitor_info_query.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)
