# Makefile

RM = rm -f
CXX = g++
CXXFLAGS = -Wall -g
INCLUDE = 
LDFLAGS = -lprofiler -lunwind
LDPATH = 

PROGS =	demo

.PHONY: all
all: $(PROGS)
	@echo "build OK!"

clean:
	@$(RM) $(PROGS) *.o *.prof *.pdf
	@echo "clean OK!"

%.o:%.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS) $(INCLUDE)

demo: demo.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)

demo.prof: demo
	./demo

pprof-text: demo demo.prof
	pprof --text demo demo.prof

pprof-pdf: demo demo.prof
	pprof --pdf demo demo.prof > demo.pdf
