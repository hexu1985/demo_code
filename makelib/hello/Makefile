
RM = rm -f
CXX = g++
CXXFLAGS = -Wall -g -c #-DNDEBUG
TARGETS = hello

.PHONY: all
all: $(TARGETS)
	@echo "build OK!"

.PHONY: clean
clean:
	$(RM) $(TARGETS) *.o

.PHONY: distclean
distclean:
	$(RM) $(TARGETS) *.o

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $<

hello: hello.o main.o
	$(CXX) -o $@ $^


