# Makefile

RM = rm -f
CXX = g++
CXXFLAGS = -Wall -g
INCLUDE = 
LDFLAGS = 
LDPATH = 

OBJS = auto_timestamp_ofile.o utc_to_string.o
PROGS =	file_write file_write2 file_write3 

.PHONY: all
all: $(PROGS)
	@echo "build OK!"

clean:
	@$(RM) $(PROGS) *.o
	@echo "clean OK!"

%.o:%.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS) $(INCLUDE)

file_write: file_write.o $(OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)

file_write2: file_write2.o $(OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)

file_write3: file_write3.o $(OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)

