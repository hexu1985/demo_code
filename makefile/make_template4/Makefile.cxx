# Makefile

RM = rm -f
CXX = g++
CXXFLAGS = -Wall -g
INCLUDE = 
LDFLAGS = 
LDPATH = 

PROGS =	test1 test2 test3

.PHONY: all
all: $(PROGS)
	@echo "build OK!"

clean:
	@$(RM) $(PROGS) *.o
	@echo "clean OK!"

%.o:%.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS) $(INCLUDE)

test1: test1.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)

test2: test2.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)

test3: test3.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)

