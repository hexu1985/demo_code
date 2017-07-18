
RM = rm -f
CXX = g++
CXXFLAGS = -Wall -g #-static
INCLUDES = 
LDFLAGS = -lPocoUtil -lPocoNet -lPocoXML -lPocoJSON -lPocoFoundation
LDPATH =

SOURCES = $(shell ls *.cpp)
PROGS = $(SOURCES:%.cpp=%)

all: $(PROGS)
	@echo "PROGS = $(PROGS)" 

clean:
	$(RM) $(PROGS)

%: %.cpp
	$(CXX) -o $@ $(CXXFLAGS) $(INCLUDES) $^ $(LDFLAGS) $(LDPATH)
