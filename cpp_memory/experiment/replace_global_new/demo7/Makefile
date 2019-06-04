# Makefile

RM = rm -f
CXX = g++
CXXFLAGS = -Wall -g
#INCLUDE = -I./libmynew
#LDFLAGS = -lmynew
LDFLAGS = ./libmynew/libmynew.a
#LDPATH = -L./libmynew

PROGS =	demo

.PHONY: all
all: $(PROGS)
	@echo "build OK!"

clean:
	@$(RM) $(PROGS) *.o
	@echo "clean OK!"

%.o:%.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS) $(INCLUDE)

demo: demo.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)

