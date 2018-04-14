# Makefile

RM = rm -f
CXX = g++
CXXFLAGS = -Wall -g 
INCLUDE = 
LDFLAGS = -lboost_program_options -lpthread -lrt
LDPATH =

PROGS =	parse_file parser_test

.PHONY: all
all: $(PROGS)
	@echo "build OK!"

clean:
	@$(RM) $(PROGS) *.o
	@echo "clean OK!"

%.o:%.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS) $(INCLUDE)

parse_file: config_parser.o config_parser_util.o parse_file.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)

