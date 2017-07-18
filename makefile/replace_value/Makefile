
SOURCES = $(shell ls *.cpp)
PROGS = $(SOURCES:%.cpp=%)

all: $(PROGS)
	@echo "PROGS = $(PROGS)" 

clean:
	rm -f $(PROGS)

%: %.cpp
	g++ $^ -o $@
