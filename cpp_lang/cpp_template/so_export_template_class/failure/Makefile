# Makefile

RM = rm -f
CXX = g++
CXXFLAGS = -Wall -g
INCLUDE = -I./hello
LDFLAGS = -lhello
LDPATH = -L./hello

PROGS =	test 

.PHONY: all
all: $(PROGS)
	@echo "build OK!"

clean:
	@$(RM) $(PROGS) *.o
	@echo "clean OK!"

%.o:%.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS) $(INCLUDE)

test: test.o
	$(CXX) -o $@ $^ -Wl,-R./hello -Wl,--enable-new-dtags $(LDFLAGS) $(LDPATH)

