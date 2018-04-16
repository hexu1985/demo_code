# Makefile

RM = rm -f
CXX = g++
CXXFLAGS = -Wall -g
INCLUDE = 
LDFLAGS = 
LDPATH = 

OBJS = error.o wraptermios.o
PROGS =	tty_open tty_open_easy tty_set_speed tty_set_parity

.PHONY: all
all: $(PROGS)
	@echo "build OK!"

clean:
	@$(RM) $(PROGS) *.o
	@echo "clean OK!"

%.o:%.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS) $(INCLUDE)

tty_open: tty_open.o $(OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)

tty_open_easy: tty_open_easy.o $(OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)

tty_set_speed: tty_set_speed.o $(OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)

tty_set_parity: tty_set_parity.o $(OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)

