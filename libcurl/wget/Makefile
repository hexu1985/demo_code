# Makefile

RM = rm -f
CXX = g++
CXXFLAGS = -Wall -g
INCLUDE = 
LDFLAGS = -lcurl
LDPATH = 

PROGS =	wget

.PHONY: all
all: $(PROGS)
	@echo "build OK!"

clean:
	@$(RM) $(PROGS) *.o
	@echo "clean OK!"

%.o:%.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS) $(INCLUDE)

wget: wget.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)

