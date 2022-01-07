
RM = rm -f
AR = ar rcs
CREATE_SO = g++ -shared
CXX = g++
CXXFLAGS = -fPIC -Wall -g -DNDEBUG 
INCLUDES = 
LDFLAGS = 
LDPATH =
VPATH = 

SOURCES = $(shell ls *.cpp)
OBJECTS = $(SOURCES:%.cpp=%.o)
DYNAMICLIB = liblib2.so
STATICLIB = liblib2.a

all: $(DYNAMICLIB) $(STATICLIB) 
	@echo "DYNAMICLIB = $(DYNAMICLIB)" 
	@echo "STATICLIB = $(STATICLIB)" 

.PHONY: clean
clean:
	$(RM) $(DYNAMICLIB) $(STATICLIB) $(OBJECTS)

$(OBJECTS): %.o: %.cpp
	$(CXX) -o $@ -c $(CXXFLAGS) $(INCLUDES) $<

$(DYNAMICLIB): $(OBJECTS)
	$(CREATE_SO) -o $(DYNAMICLIB) $(OBJECTS)

$(STATICLIB): $(OBJECTS)
	$(AR) $(STATICLIB) $(OBJECTS)

