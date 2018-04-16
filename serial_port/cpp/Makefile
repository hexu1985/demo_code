# Makefile

RM = rm -f
CXX = g++
CXXFLAGS = -Wall -g
INCLUDE = 
LDFLAGS = 
LDPATH = 

OBJS = error.o wraptermios.o
PROGS =	open open_for_read open_for_write set_speed

.PHONY: all
all: $(PROGS)
	@echo "build OK!"

clean:
	@$(RM) $(PROGS) *.o
	@echo "clean OK!"

%.o:%.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS) $(INCLUDE)

open: open.o $(OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)

open_for_read: open_for_read.o $(OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)

open_for_write: open_for_write.o $(OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)

set_speed: set_speed.o $(OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)

