# Makefile

RMR = rm -rf
RM = rm -f
CXX = g++

VPATH = 
CXXFLAGS = -Wall -g -DDEBUG 
INCLUDE = 
LDFLAGS = -lprotobuf
LDPATH = -L/usr/local/lib

OBJS = addressbook.pb.o

PROGS = write read

.PHONY: all
all: $(PROGS)
	@echo "build OK!"

.PHONY: clean
clean:
	$(RM) $(PROGS) *.o *.obj *.exe
	@echo "clean OK!"

.PHONY: proto
proto: addressbook.proto
	protoc --cpp_out=. $<

.PHONY: distclean
distclean: proto-clean clean 

.PHONY: proto-clean
proto-clean:
	$(RM) *.pb.h *.pb.cc 

%.o:%.cc
	$(CXX) -o $@ -c $< $(CXXFLAGS) $(INCLUDE)

write: write.o $(OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)

read: read.o $(OBJS)
	@$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)


