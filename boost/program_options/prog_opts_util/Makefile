# Makefile

RM = rm -f
CXX = g++
CXXFLAGS = -Wall -g 
INCLUDE = 
LDFLAGS = -lboost_program_options -lpthread -lrt
LDPATH =

PROGS =	test

.PHONY: all
all: $(PROGS)
	@echo "build OK!"

clean:
	@$(RM) $(PROGS) *.o
	@echo "clean OK!"

%.o:%.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS) $(INCLUDE)

test: prog_opts_util.o main.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)

