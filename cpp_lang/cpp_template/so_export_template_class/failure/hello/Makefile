
RM = rm -f
CREATE_SO = g++ -shared
CXX = g++
CXXFLAGS = -fPIC -Wall -g -DNDEBUG -fvisibility=hidden -fpermissive
INCLUDES = 
LDFLAGS = 
LDPATH =
VPATH = 

SOURCES = $(shell ls *.cpp)
OBJECTS = $(SOURCES:%.cpp=%.o)
DYNAMICLIB = libhello.so

all: $(DYNAMICLIB)
	@echo "DYNAMICLIB = $(DYNAMICLIB)" 

clean:
	$(RM) $(OBJECTS)

.PHONY: distclean
distclean:
	$(RM) $(DYNAMICLIB) $(OBJECTS)

$(OBJECTS): %.o: %.cpp
	$(CXX) -o $@ -c $(CXXFLAGS) $(INCLUDES) $<

$(DYNAMICLIB): $(OBJECTS)
	$(CREATE_SO) -o $(DYNAMICLIB) $(OBJECTS)

