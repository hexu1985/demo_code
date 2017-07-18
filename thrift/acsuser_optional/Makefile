# Makefile

RMR = rm -rf
RM = rm -f
CXX = g++

VPATH = ./gen-cpp
CXXFLAGS = -Wall -g -DDEBUG -DHAVE_INTTYPES_H -DHAVE_NETINET_IN_H
INCLUDE = -I./gen-cpp
LDFLAGS = -lthrift -lrt
LDPATH = -L/usr/local/lib

OBJS = acsuser_constants.o acsuser_types.o UserService.o

PROGS = UserClient UserServer 

.PHONY: all
all: $(PROGS)
	@echo "build OK!"

.PHONY: clean
clean:
	$(RM) $(PROGS) *.o *.obj *.exe
	@echo "clean OK!"

.PHONY: thrift
thrift: acsuser.thrift
	thrift --gen cpp $<
	thrift --gen py $<

.PHONY: distclean
distclean: thrift-clean clean 

.PHONY: thrift-clean
thrift-clean:
	$(RMR) ./gen-cpp ./gen-py

%.o:%.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS) $(INCLUDE)

UserClient: UserClient.o $(OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)

UserServer: UserServer.o $(OBJS)
	@$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)


