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

PROGS = add_person list_people test

.PHONY: all
all: $(PROGS)
	@echo "build OK!"

.PHONY: clean
clean:
	$(RM) $(PROGS) *.o *.obj *.exe *.pyc
	@echo "clean OK!"

.PHONY: proto
proto: addressbook.proto
	protoc --cpp_out=. --python_out=. $<

.PHONY: distclean
distclean: proto-clean clean 

.PHONY: proto-clean
proto-clean:
	$(RM) *.pb.h *.pb.cc 

%.o:%.cc
	$(CXX) -o $@ -c $< $(CXXFLAGS) $(INCLUDE)

add_person: add_person.o $(OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)

list_people: list_people.o $(OBJS)
	@$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)

test: test.o $(OBJS)
	@$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)


