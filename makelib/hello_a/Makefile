
AR = ar r
RM = rm -f
CXX = g++
CXXFLAGS = -Wall -g -c #-DNDEBUG
TARGETS = hello
LIB_OBJS = hello.o
LIB_NAME = libhello.a

.PHONY: all
all: $(TARGETS)
	@echo "build OK!"

.PHONY: clean
clean:
	$(RM) $(TARGETS)

.PHONY: distclean
distclean:
	$(RM) $(TARGETS) *.o *.a

$(LIB_NAME): $(LIB_OBJS)
	$(AR) $(LIB_NAME) $(LIB_OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $^

hello: main.o $(LIB_NAME)
	$(CXX) -o $@ $^


