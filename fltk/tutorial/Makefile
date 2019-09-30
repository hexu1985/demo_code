
RM = rm -f
CXX = g++
CXXFLAGS = -Wall -g 
INCLUDES = 
# fltk-config --ldflags
LDFLAGS = -lfltk -lfltk_images $(shell fltk-config --ldflags)
LDPATH =

SOURCES = $(shell ls *.cpp)
PROGS = $(SOURCES:%.cpp=%)

all: $(PROGS)
	@echo "PROGS = $(PROGS)" 

clean:
	$(RM) $(PROGS)

%: %.cpp
	$(CXX) -o $@ $(CXXFLAGS) $(INCLUDES) $^ $(LDFLAGS) $(LDPATH)
