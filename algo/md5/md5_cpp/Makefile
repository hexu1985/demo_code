# Makefile

RM = rm -f
CXX = g++
CFLAGS = -Wall -g
INCLUDE = 
LDFLAGS = 
LDPATH = 

PROGS =	test_md5

.PHONY: all
all: $(PROGS)
	@echo "build OK!"

clean:
	@$(RM) $(PROGS) *.o
	@echo "clean OK!"

%.o:%.cpp
	$(CXX) -o $@ -c $< $(CFLAGS) $(INCLUDE)

test_md5: md5.o test_md5.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)

