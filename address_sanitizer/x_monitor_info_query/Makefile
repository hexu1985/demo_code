
RM = rm -f
CXX = g++
CXXFLAGS = -Wall -g -std=c++11 -fsanitize=address -fno-omit-frame-pointer
INCLUDES = 
#LDFLAGS = -lXrandr -lXinerama -lXext -lX11 -lpthread
LDFLAGS = -lasan -lXrandr -lX11 -lpthread 
LDPATH =

SOURCES = $(shell ls *.cpp)
PROGS = get_screen_info listen_screen_update

all: $(PROGS)
	@echo "PROGS = $(PROGS)" 

clean:
	$(RM) $(PROGS) *.o

%.o:%.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS) $(INCLUDE)

get_screen_info: get_screen_info.o x_monitor_info_query.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)

listen_screen_update: listen_screen_update.o x_monitor_info_query.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)
