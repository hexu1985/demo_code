
RM = rm -f
CXX = g++
CXXFLAGS = -Wall -g -std=c++11
INCLUDES = 
#LDFLAGS = -lXrandr -lXinerama -lXext -lX11 -lpthread
LDFLAGS = -lXrandr -lX11 -lpthread
LDPATH =

SOURCES = $(shell ls *.cpp)
PROGS = get_screen_info

all: $(PROGS)
	@echo "PROGS = $(PROGS)" 

clean:
	$(RM) $(PROGS) *.o

%.o:%.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS) $(INCLUDE)

get_screen_info: get_screen_info.o x_monitor_info_query.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)
