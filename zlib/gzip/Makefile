# Makefile

RM = rm -f
CXX = g++
CXXFLAGS = -Wall -g -DNDEBUG -std=c++14
INCLUDES = -I..
LDFLAGS = -lzlibstatic
LDPATH = -L../zlib/build

PROGS =	gzip gunzip

.PHONY: all
all: $(PROGS)
	@echo "build OK!"

clean:
	@$(RM) $(PROGS) *.o
	@echo "clean OK!"

%.o:%.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS) $(INCLUDES)

gzip: gzip.o gzcompress.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)

gunzip: gunzip.o gzcompress.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)


