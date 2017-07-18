# Makefile

RM = rm -f
CXX = g++
CXXFLAGS = -Wall -g
INCLUDE = -I../include -I${GTESTROOT}/include
LDFLAGS = -lcpphx -lgtest
LDPATH = -L../src -L${GTESTROOT}/lib/.libs

OBJS = main.o basic_test.o
PROGS = basic_test

.PHONY: all
all: $(PROGS)
	@echo "build OK!"

clean:
	@$(RM) $(PROGS) *.o
	@echo "clean OK!"

$(OBJS):%.o:%.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS) $(INCLUDE)

basic_test: main.o basic_test.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)
