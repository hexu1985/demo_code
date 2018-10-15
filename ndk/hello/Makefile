
RM = rm -f
CXX = /opt/android-ndk-r14b/android-aarch64/bin/clang++
# CXXFLAGS = -Wall -g -static # all lib link into executable file
CXXFLAGS = -Wall -g -pie -fPIE 
INCLUDES = 
LDFLAGS =
LDPATH = 

SOURCES = $(shell ls *.cpp)
PROGS = $(SOURCES:%.cpp=%)

all: $(PROGS)
	@echo "PROGS = $(PROGS)" 

clean:
	$(RM) $(PROGS)

%: %.cpp
	$(CXX) -o $@ $(CXXFLAGS) $(INCLUDES) $^ $(LDFLAGS) $(LDPATH)
