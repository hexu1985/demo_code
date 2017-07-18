# Makefile

RM = rm -f
CXX = g++
CXXFLAGS = -Wall -g
INCLUDE = -I${GTESTROOT}/include
LDFLAGS = -lgtest
LDPATH = -L${GTESTROOT}/lib/.libs

OBJS = main.o assigning.o constructor.o size.o length.o capacity.o resize.o
PROGS = constructor assigning size length capacity resize test_string_all 

.PHONY: all
all: $(PROGS)
	@echo "build OK!"

clean:
	@$(RM) $(PROGS) *.o
	@echo "clean OK!"

$(OBJS):%.o:%.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS) $(INCLUDE)

# test constructor
constructor: main.o constructor.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)

# test operator =
assigning: main.o assigning.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)

# test size()
size: main.o size.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)

# test length()
length: main.o length.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)

# test capacity()
capacity: main.o capacity.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)

# test resize()
resize: main.o resize.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)

# test string all api
test_string_all: $(OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)
