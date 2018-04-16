# Makefile

RM = rm -f
CXX = g++
CXXFLAGS = -Wall -g
INCLUDE = 
LDFLAGS = 
LDPATH = 

OBJS = error.o wraptermios.o wrapunix.o
PROGS =	tty_open tty_open_easy tty_set_speed tty_set_parity tty_set_timeout \
		tty_read tty_write tty_read_select

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

tty_set_timeout: tty_set_timeout.o $(OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)

tty_read: tty_read.o $(OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)

tty_read_select: tty_read_select.o $(OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)

tty_write: tty_write.o $(OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)

