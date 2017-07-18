# Makefile

RM = rm -f
CXX = g++
CXXFLAGS = -Wall -g -std=c++11
INCLUDE = 
LDFLAGS = -lboost_program_options
LDPATH = 

PROGS =	our_program case1 case3 case4 case5 case6

.PHONY: all
all: $(PROGS)
	@echo "build OK!"

clean:
	@$(RM) $(PROGS) *.o
	@echo "clean OK!"

%.o:%.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS) $(INCLUDE)

our_program: our_program.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)

case1: case1.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)

case3: case3.o print_vm.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)

case4: case4.o print_vm.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)

case5: case5.o print_vm.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)

case6: case6.o print_vm.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)

