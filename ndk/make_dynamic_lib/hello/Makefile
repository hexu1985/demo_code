
RM = rm -f
CREATE_SO = /opt/android-ndk-r16b-clang/android-aarch64/bin/aarch64-linux-android-clang++ -shared
CXX = /opt/android-ndk-r16b-clang/android-aarch64/bin/aarch64-linux-android-clang++
CXXFLAGS = -fPIC -Wall -g -DNDEBUG #-fPIE
INCLUDES = 
LDFLAGS = 
LDPATH =
VPATH = 

SOURCES = $(shell ls *.cpp)
OBJECTS = $(SOURCES:%.cpp=%.o)
DYNAMICLIB = libhello.so
DYNAMICLIB_WITH_CXX_LIB = libhello_with_cxx_lib.so

all: $(DYNAMICLIB) $(DYNAMICLIB_WITH_CXX_LIB)
	@echo "DYNAMICLIB = $(DYNAMICLIB)" 

clean:
	$(RM) $(DYNAMICLIB) $(DYNAMICLIB_WITH_CXX_LIB) $(OBJECTS)

.PHONY: distclean
distclean:
	$(RM) $(DYNAMICLIB) $(OBJECTS)

$(OBJECTS): %.o: %.cpp
	$(CXX) -o $@ -c $(CXXFLAGS) $(INCLUDES) $<

$(DYNAMICLIB): $(OBJECTS)
	$(CREATE_SO) -o $@ $(OBJECTS)

$(DYNAMICLIB_WITH_CXX_LIB): $(OBJECTS)
	$(CREATE_SO) -o $@ $(OBJECTS) -static-libstdc++
