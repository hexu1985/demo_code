
CREATE_SO = g++ -shared
RM = rm -f
CXX = g++
CXXFLAGS = -Wall -g -c #-DNDEBUG
TARGETS = class_factory
LIB1_OBJS = derived1.o
LIB1_NAME = libderived1.so
LIB2_OBJS = derived2.o
LIB2_NAME = libderived2.so

.PHONY: all
all: $(TARGETS) $(LIB1_NAME) $(LIB2_NAME)
	@echo "build OK!"

.PHONY: clean
clean:
	$(RM) $(TARGETS) *.o *.so

.PHONY: distclean
distclean:
	$(RM) $(TARGETS) *.o *.so

$(LIB1_NAME): $(LIB1_OBJS) base.o
	$(CREATE_SO) $^ -o $(LIB1_NAME) 

$(LIB2_NAME): $(LIB2_OBJS) base.o
	$(CREATE_SO) $^ -o $(LIB2_NAME) 

$(LIB1_OBJS):%.o: %.cpp
	$(CXX) $(CXXFLAGS) -fPIC $^

$(LIB2_OBJS):%.o: %.cpp
	$(CXX) $(CXXFLAGS) -fPIC $^

base.o: base.cpp
	$(CXX) $(CXXFLAGS) -fPIC $<

main.o: main.cpp
	$(CXX) $(CXXFLAGS) $<

class_factory: main.o
	$(CXX) -o $@ $^ -ldl

