# Makefile

RM = rm -f
CXX = g++
CXXFLAGS = -Wall -O3 -std=c++11
INCLUDE = 
LDFLAGS = 
LDPATH = 

PROGS =	any any2

.PHONY: all
all: $(PROGS)
	@echo "build OK!"

clean:
	@$(RM) $(PROGS) *.o
	@echo "clean OK!"

%.o:%.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS) $(INCLUDE)

any: any.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)

any2: any2.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)

