# Makefile

RM = rm -f
CXX = g++
CXXFLAGS = -Wall -g
INCLUDE = -I./my_library
LDFLAGS = -lmy_library
LDPATH = -L./my_library

PROGS =	use_library

.PHONY: all
all: $(PROGS)
	@echo "build OK!"

clean:
	@$(RM) $(PROGS) *.o
	@echo "clean OK!"

%.o:%.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS) $(INCLUDE)

use_library: use_library.o
#	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)
#	$(CXX) -o $@ $^ -Wl,-R./my_library $(LDFLAGS) $(LDPATH)
	$(CXX) -o $@ $^ -Wl,-R./my_library -Wl,--enable-new-dtags $(LDFLAGS) $(LDPATH)

