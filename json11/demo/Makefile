# Makefile

RM = rm -f
CXX = g++
CXXFLAGS = -Wall -g
INCLUDE = -I../json11
LDFLAGS = 
LDPATH = 

PROGS =	read read_from_file array write read_write
VPATH = ../json11

.PHONY: all
all: $(PROGS)
	@echo "build OK!"

clean:
	@$(RM) $(PROGS) *.o
	@echo "clean OK!"

%.o:%.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS) $(INCLUDE)

read: read.o json11.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)

read_from_file: read_from_file.o json11.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)

array: array.o json11.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)

write: write.o json11.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)

read_write: read_write.o json11.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)


