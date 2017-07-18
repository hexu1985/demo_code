# Makefile

RMR = rm -rf
RM = rm -f
CXX = g++

VPATH = ./gen-cpp
CXXFLAGS = -Wall -g -DDEBUG -DHAVE_INTTYPES_H -DHAVE_NETINET_IN_H -std=c++11
INCLUDE = -I./gen-cpp
LDFLAGS = -lthriftnb -levent -lthrift -lrt -pthread
LDPATH = -L/usr/local/lib

OBJS = student_constants.o student_types.o Serv.o

PROGS = client server client_sleep client_race

.PHONY: all
all: $(PROGS)
	@echo "build OK!"

.PHONY: clean
clean:
	$(RM) $(PROGS) *.o *.obj *.exe
	@echo "clean OK!"

.PHONY: thrift
thrift: student.thrift
	thrift --gen cpp $<

.PHONY: distclean
distclean: thrift-clean clean 

.PHONY: thrift-clean
thrift-clean:
	$(RMR) ./gen-cpp

%.o:%.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS) $(INCLUDE)

client: client.o $(OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)

client_sleep: client_sleep.o $(OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)

client_race: client_race.o $(OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)

server: server.o $(OBJS)
	@$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)


