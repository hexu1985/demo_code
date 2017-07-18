# Makefile

RM = rm -f
CXX = g++
CXXFLAGS = -Wall -O3 -std=c++11
INCLUDE = 
LDFLAGS = 
LDPATH = 

PROGS =	pool pool2 object_pool malloc pool_malloc pool_malloc2

.PHONY: all
all: $(PROGS)
	@echo "build OK!"

clean:
	@$(RM) $(PROGS) *.o
	@echo "clean OK!"

%.o:%.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS) $(INCLUDE)

pool: pool.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)

pool2: pool2.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)

object_pool: object_pool.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)

malloc: malloc.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)

pool_malloc: pool_malloc.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)

pool_malloc2: pool_malloc2.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)

