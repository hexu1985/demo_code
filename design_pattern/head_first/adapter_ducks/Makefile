# Makefile

RM = rm -f
CXX = g++
CXXFLAGS = -Wall -g
INCLUDE = 
LDFLAGS = 
LDPATH = 

PROGS =	duck_test_drive turkey_test_drive

.PHONY: all
all: $(PROGS)
	@echo "build OK!"

clean:
	@$(RM) $(PROGS) *.o
	@echo "clean OK!"

%.o:%.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS) $(INCLUDE)

duck_test_drive: duck_test_drive.o wild_turkey.o turkey_adapter.o mallar_duck.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)

turkey_test_drive: turkey_test_drive.o mallar_duck.o duck_adapter.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)


