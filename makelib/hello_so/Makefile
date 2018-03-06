
CREATE_SO = g++ -shared
RM = rm -f
CXX = g++
CXXFLAGS = -Wall -g -c -DNDEBUG
TARGETS = main 
LIB_OBJS = hello.o
LIB_NAME = libhello.so

.PHONY: all
all: $(TARGETS)
	@echo "build OK!"

.PHONY: clean
clean:
	$(RM) $(TARGETS) *.o *.so

$(LIB_NAME): $(LIB_OBJS)
	$(CREATE_SO) $(LIB_OBJS) -o $(LIB_NAME) 

$(LIB_OBJS):%.o: %.cpp
	$(CXX) $(CXXFLAGS) -fPIC $^

main.o: main.cpp
	$(CXX) $(CXXFLAGS) $^

main: main.o $(LIB_NAME)
	$(CXX) -o $@ $^

