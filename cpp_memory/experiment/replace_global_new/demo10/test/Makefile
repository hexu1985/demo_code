
RM = rm -f
CXX = g++
CXXFLAGS = -Wall -g
INCLUDES = -I../lib1 -I../lib2
LDFLAGS = -llib1 -llib2 -lmynew
#LDFLAGS = ../lib1/liblib1.a ../libmynew/libmynew.a ../lib2/liblib2.a 
LDPATH = -L../lib1 -L../lib2 -L../libmynew

SOURCES = $(shell ls *.cpp)
PROGS = $(SOURCES:%.cpp=%)

all: $(PROGS)
	@echo "PROGS = $(PROGS)" 

clean:
	$(RM) $(PROGS)

%: %.cpp
	$(CXX) -o $@ $(CXXFLAGS) $(INCLUDES) $^ $(LDFLAGS) $(LDPATH)
