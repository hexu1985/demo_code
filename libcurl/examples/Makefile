# Makefile

RM = rm -f
CXX = gcc
CXXFLAGS = -Wall -g
INCLUDE = 
LDFLAGS = -lcurl
LDPATH = 

PROGS =	http-post https simple simplepost

.PHONY: all
all: $(PROGS)
	@echo "build OK!"

clean:
	@$(RM) $(PROGS) *.o
	@echo "clean OK!"

%.o:%.c
	$(CXX) -o $@ -c $< $(CXXFLAGS) $(INCLUDE)

http-post: http-post.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)

https: https.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)

simple: simple.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)

simplepost: simplepost.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)

