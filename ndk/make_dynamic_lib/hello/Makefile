
RM = rm -f
CREATE_SO = /opt/android-ndk-r14b/android-aarch64/bin/aarch64-linux-android-clang++ -shared 
CXX = /opt/android-ndk-r14b/android-aarch64/bin/aarch64-linux-android-clang++
CXXFLAGS = -fPIC -Wall -g -DNDEBUG #-fPIE
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
	$(RM) $(DYNAMICLIB) $(OBJECTS)

.PHONY: distclean
distclean:
	$(RM) $(DYNAMICLIB) $(OBJECTS)

$(OBJECTS): %.o: %.cpp
	$(CXX) -o $@ -c $(CXXFLAGS) $(INCLUDES) $<

$(DYNAMICLIB): $(OBJECTS)
	$(CREATE_SO) -o $(DYNAMICLIB) $(OBJECTS)

