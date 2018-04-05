
RM = rm -f
CXX = g++
CXXFLAGS = -Wall -g
INCLUDES = -I/usr/include/oracle/11.1.0.1/client64 
LDFLAGS = -locci -lclntsh -lnnz11
LDPATH = -Wl,-R/usr/lib/oracle/11.1.0.1/client64/lib -Wl,--enable-new-dtags -L/usr/lib/oracle/11.1.0.1/client64/lib

SOURCES = $(shell ls *.cpp)
PROGS = $(SOURCES:%.cpp=%)

all: $(PROGS)
	@echo "PROGS = $(PROGS)" 

clean:
	$(RM) $(PROGS)

%: %.cpp
	$(CXX) -o $@ $(CXXFLAGS) $(INCLUDES) $^ $(LDFLAGS) $(LDPATH)
