# Makefile

RMR = rm -rf
RM = rm -f
CXX = g++

VPATH = ./gen-cpp
CXXFLAGS = -Wall -g -DDEBUG -DHAVE_INTTYPES_H -DHAVE_NETINET_IN_H
INCLUDE = -I./gen-cpp
LDFLAGS = -lthrift
LDPATH = -L/usr/local/lib

OBJS = echo_constants.o echo_types.o EchoTest.o

PROGS = client server client_catch server_throw

.PHONY: all
all: $(PROGS)
	@echo "build OK!"

.PHONY: clean
clean:
	$(RM) $(PROGS) *.o *.obj *.exe
	@echo "clean OK!"

.PHONY: thrift
thrift: echo.thrift
	thrift --gen cpp $<
	thrift --gen py $<

.PHONY: distclean
distclean: thrift-clean clean 

.PHONY: thrift-clean
thrift-clean:
	$(RMR) ./gen-cpp ./gen-py

%.o:%.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS) $(INCLUDE)

client: client.o $(OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)

server: server.o $(OBJS)
	@$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)

client_catch: client_catch.o $(OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)

server_throw: server_throw.o $(OBJS)
	@$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)


