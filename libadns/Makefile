# Makefile

RM = rm -f
CXX = g++
CFLAGS = -Wall -g
INCLUDE = 
LDFLAGS = -ladns
LDPATH = 

PROGS =	hostent hostent2 hostent3

.PHONY: all
all: $(PROGS)
	@echo "build OK!"

clean:
	@$(RM) $(PROGS) *.o
	@echo "clean OK!"

%.o:%.cpp
	$(CXX) -o $@ -c $< $(CFLAGS) $(INCLUDE)

hostent: hostent.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)

hostent2: hostent2.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)

hostent3: hostent3.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)

