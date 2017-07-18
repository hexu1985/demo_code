# Makefile

RMR = rm -rf
RM = rm -f
CXX = g++

VPATH = ./gen-cpp
CXXFLAGS = -Wall -g -DDEBUG -DHAVE_INTTYPES_H -DHAVE_NETINET_IN_H
INCLUDE = -I./gen-cpp
LDFLAGS = -lthrift
LDPATH = -L/usr/local/lib

OBJS = demo_constants.o demo_types.o DemoService.o enums_constants.o enums_types.o

PROGS = DemoServer DemoClient

.PHONY: all
all: $(PROGS)
	@echo "build OK!"

.PHONY: clean
clean:
	$(RM) $(PROGS) *.o *.obj *.exe
	@echo "clean OK!"

.PHONY: thrift
thrift: demo.thrift enums.thrift
	thrift --gen cpp enums.thrift
	thrift --gen cpp demo.thrift

.PHONY: distclean
distclean: thrift-clean clean 

.PHONY: thrift-clean
thrift-clean:
	$(RMR) ./gen-cpp

%.o:%.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS) $(INCLUDE)

DemoClient: DemoClient.o $(OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)

DemoServer: DemoServer.o $(OBJS)
	@$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)



