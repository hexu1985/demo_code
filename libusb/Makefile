
RM = rm -f
CXX = g++
CXXFLAGS = -Wall -g
INCLUDES = -Iinclude/libusb
LDFLAGS = -lusb -ludev -lpthread
LDPATH = -Llibs

SOURCES = $(shell ls *.cpp)
PROGS = $(SOURCES:%.cpp=%)

all: $(PROGS)
	@echo "PROGS = $(PROGS)" 

clean:
	$(RM) $(PROGS)

%: %.cpp
	$(CXX) -o $@ $(CXXFLAGS) $(INCLUDES) $^ $(LDFLAGS) $(LDPATH)
