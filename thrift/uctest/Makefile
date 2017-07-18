# Makefile

RMR = rm -rf
RM = rm -f
CXX = g++

VPATH = ./gen-cpp
CXXFLAGS = -Wall -std=c++11 -g -DDEBUG -DHAVE_INTTYPES_H -DHAVE_NETINET_IN_H
INCLUDE = -I./gen-cpp
LDFLAGS = -lthrift -lthriftnb -lrt -levent
LDPATH = -L/usr/local/lib

OBJS = test_constants.o test_types.o Test.o

PROGS = TestClient TestServer 

.PHONY: all
all: $(PROGS)
	@echo "build OK!"

.PHONY: clean
clean:
	$(RM) $(PROGS) *.o *.obj *.exe
	@echo "clean OK!"

.PHONY: thrift
thrift: test.thrift
	thrift --gen cpp:cob_style $<

.PHONY: distclean
distclean: thrift-clean clean 

.PHONY: thrift-clean
thrift-clean:
	$(RMR) ./gen-cpp ./gen-py

%.o:%.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS) $(INCLUDE)

TestClient: TestClient.o $(OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)

TestServer: TestServer.o $(OBJS)
	@$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)


