# suffix rule

CC = gcc
CXX = g++

PROGS = hello_c hello_cpp

all: $(PROGS)

clean:
	rm -f $(PROGS)

%: %.c
	$(CC) $^ -o $@

%: %.cpp
	$(CXX) $^ -o $@

