
RM = rm -f
CXX = g++
CXXFLAGS = -Wall -g -c #-DNDEBUG
TARGETS = say_hello_1 say_hello_2 say_hello_a say_hello_so
LIB_A_NAME = libhello_bye.a
LIB_SO_NAME = libhello_bye.so

.PHONY: all
all: $(TARGETS)
	@echo "build OK!"

.PHONY: clean
clean:
	$(RM) $(TARGETS) $(LIB_A_NAME) $(LIB_SO_NAME) *.o

.PHONY: distclean
distclean:
	$(RM) $(TARGETS) *.o

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $<

say_hello_1: main.o hello.o
	$(CXX) -o $@ $^

say_hello_2: main.o hello.o bye.o
	$(CXX) -o $@ $^

say_hello_a: main.o $(LIB_A_NAME)
	$(CXX) -o $@ $^

say_hello_so: main.o $(LIB_SO_NAME)
	$(CXX) -o $@ $^


