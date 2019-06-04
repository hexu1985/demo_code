
RM = rm -f
AR = ar rcs
CXX = g++
CXXFLAGS = -Wall -g -DNDEBUG 
INCLUDES = 
LDFLAGS = 
LDPATH =
VPATH = 

SOURCES = $(shell ls *.cpp)
OBJECTS = $(SOURCES:%.cpp=%.o)
STATICLIB = libmynew.a

all: $(STATICLIB)
	@echo "STATICLIB = $(STATICLIB)" 

clean:
	$(RM) $(STATICLIB) $(OBJECTS)

$(OBJECTS): %.o: %.cpp
	$(CXX) -o $@ -c $(CXXFLAGS) $(INCLUDES) $<

$(STATICLIB): $(OBJECTS)
	$(AR) $(STATICLIB) $(OBJECTS)

