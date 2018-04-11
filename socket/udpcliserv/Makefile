# Makefile

RM = rm -f
CXX = g++
CXXFLAGS = -Wall -g
INCLUDE = 
LDFLAGS = 
LDPATH = 

PROGS =	udpcli01 udpserv01

.PHONY: all
all: $(PROGS)
	@echo "build OK!"

clean:
	@$(RM) $(PROGS) *.o
	@echo "clean OK!"

%.o:%.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS) $(INCLUDE)

udpcli01: udpcli01.o dg_cli.o wraplib.o wrapsock.o wrapstdio.o error.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)

udpserv01: udpserv01.o dg_echo.o wrapsock.o error.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)


