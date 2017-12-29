# Makefile

RM = rm -f
CXX = g++
CXXFLAGS = -Wall -g
INCLUDE = 
LDFLAGS = 
LDPATH = 

PROGS =	mini_duck_simulator mini_duck_simulator1

.PHONY: all
all: $(PROGS)
	@echo "build OK!"

clean:
	@$(RM) $(PROGS) *.o
	@echo "clean OK!"

%.o:%.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS) $(INCLUDE)

mini_duck_simulator: mini_duck_simulator.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)

mini_duck_simulator1: mini_duck_simulator1.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)


