
CREATE_SO = g++ -shared
RM = rm -f
CXX = g++
CXXFLAGS = -Wall -g -c #-DNDEBUG
TARGETS = hello hello2
LIB_OBJS = hello.o
LIB_NAME = libhello.so

.PHONY: all
all: $(TARGETS)
	@echo "build OK!"

.PHONY: clean
clean:
	$(RM) $(TARGETS)

.PHONY: distclean
distclean:
	$(RM) $(TARGETS) *.o *.so

$(LIB_NAME): $(LIB_OBJS)
	$(CREATE_SO) $(LIB_OBJS) -o $(LIB_NAME) 

$(LIB_OBJS):%.o: %.cpp
	$(CXX) $(CXXFLAGS) -fPIC $^

main.o: main.cpp
	$(CXX) $(CXXFLAGS) $^

hello: main.o $(LIB_NAME)
	$(CXX) -o $@ $^

main2.o: main2.cpp
	$(CXX) $(CXXFLAGS) $^

hello2: main2.o
	$(CXX) -o $@ $^ -ldl

