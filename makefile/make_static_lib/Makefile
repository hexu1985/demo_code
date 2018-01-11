# Makefile

RM = rm -f
CXX = g++
CXXFLAGS = -Wall -g
INCLUDE = -I./hello
LDFLAGS = -lhello
LDPATH = -L./hello

PROGS =	test1

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

