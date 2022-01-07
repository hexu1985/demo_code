
RM = rm -f
CREATE_SO = g++ -shared
CXX = g++
CXXFLAGS = -fPIC -Wall -g -DNDEBUG 
INCLUDES = 
LDFLAGS = 
LDPATH =
VPATH = 

SOURCES = $(shell ls *.cpp)
OBJECTS = $(SOURCES:%.cpp=%.o)
DYNAMICLIB = libmynew.so

all: $(DYNAMICLIB)
	@echo "DYNAMICLIB = $(DYNAMICLIB)" 

clean:
	$(RM) $(DYNAMICLIB) $(OBJECTS)

$(OBJECTS): %.o: %.cpp
	$(CXX) -o $@ -c $(CXXFLAGS) $(INCLUDES) $<

$(DYNAMICLIB): $(OBJECTS)
	$(CREATE_SO) -o $(DYNAMICLIB) $(OBJECTS)

