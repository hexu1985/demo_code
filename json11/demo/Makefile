# Makefile

RM = rm -f
CXX = g++
CXXFLAGS = -Wall -g
INCLUDE = -I../json11
LDFLAGS = 
LDPATH = 

PROGS =	read
VPATH = ../json11

.PHONY: all
all: $(PROGS)
	@echo "build OK!"

clean:
	@$(RM) $(PROGS) *.o
	@echo "clean OK!"

%.o:%.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS) $(INCLUDE)

read: read.o json11.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)


