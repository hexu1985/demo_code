
RM = rm -f
CXX = g++
CXXFLAGS = -Wall -g
INCLUDES = -I../../../third-party/snmp++/include
LDFLAGS = -lsnmp++
LDPATH = -L../../../third-party/snmp++/lib -Wl,-R../../../third-party/snmp++/lib -Wl,--enable-new-dtags

SOURCES = $(shell ls *.cpp)
PROGS = $(SOURCES:%.cpp=%)

all: $(PROGS)
	@echo "PROGS = $(PROGS)" 

clean:
	$(RM) $(PROGS)

%: %.cpp
	$(CXX) -o $@ $(CXXFLAGS) $(INCLUDES) $^ $(LDFLAGS) $(LDPATH)
