# Makefile

RM = rm -rf
CXX = g++
CXXFLAGS = -Wall -g
INCLUDE = 
LDFLAGS = -lprofiler -lunwind -ltcmalloc
LDPATH = 

PROGS =	leak

.PHONY: all
all: $(PROGS)
	@echo "build OK!"

clean:
	@$(RM) $(PROGS) *.o *.prof *.txt *.pdf ./tmp
	@echo "clean OK!"

%.o:%.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS) $(INCLUDE)

leak: leak.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)

