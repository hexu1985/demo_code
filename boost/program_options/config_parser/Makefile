# Makefile

RM = rm -f
CXX = g++
CXXFLAGS = -Wall -g 
INCLUDE = 
LDFLAGS = -lboost_program_options -lpthread -lrt
LDPATH =

PROGS =	parse_command_line parse_environment parse_config_file parse_all

.PHONY: all
all: $(PROGS)
	@echo "build OK!"

clean:
	@$(RM) $(PROGS) *.o
	@echo "clean OK!"

%.o:%.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS) $(INCLUDE)

parse_command_line: config_parser.o config_parser_util.o parse_command_line.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)

parse_environment: config_parser.o config_parser_util.o parse_environment.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)

parse_config_file: config_parser.o config_parser_util.o parse_config_file.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)

parse_all: config_parser.o config_parser_util.o parse_all.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)

