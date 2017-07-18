# my makefile

RM = rm -f
MV = mv
AR = ar r
CXX = g++
CXXFLAGS = -Wall -c -g
INCLUDE = -I../include
LDFLAGS =
LDPATH =

TARGETS = double_linked_list.o
LIBNAME = libcpphx.a

.PHONY: all
all: $(TARGETS)
#	$(CXX) -shared -o libpacket.so $(TARGETS)
	$(AR) $(LIBNAME) $(TARGETS)

.PHONY: clean
clean:
	$(RM) $(TARGETS) $(LIBNAME)

$(TARGETS): %.o: %.cpp
	$(CXX) $(INCLUDE) $(CXXFLAGS) $^ -o $@

