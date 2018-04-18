# Makefile

RM = rm -f
CXX = g++
CXXFLAGS = -Wall -g -std=c++98
INCLUDE = 
LDFLAGS = -lboost_chrono -lboost_system
LDPATH = 

OBJS = auto_timestamp_ofile.o utc_to_string.o
PROGS =	file_write

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

