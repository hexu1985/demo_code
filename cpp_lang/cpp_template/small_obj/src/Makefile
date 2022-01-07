
RM = rm -f
AR = ar rcs
CXX = g++
CXXFLAGS = -Wall -g -DNDEBUG 
INCLUDES = -I../include
LDFLAGS = 
LDPATH =
VPATH = 

SOURCES = $(shell ls *.cpp)
OBJECTS = $(SOURCES:%.cpp=%.o)
STATICLIB = libloki.a

all: $(STATICLIB)
	@echo "STATICLIB = $(STATICLIB)" 

clean:
	$(RM) $(OBJECTS)

.PHONY: distclean
distclean:
	$(RM) $(STATICLIB) $(OBJECTS)

$(OBJECTS): %.o: %.cpp
	$(CXX) -o $@ -c $(CXXFLAGS) $(INCLUDES) $<

$(STATICLIB): $(OBJECTS)
	$(AR) $(STATICLIB) $(OBJECTS)

