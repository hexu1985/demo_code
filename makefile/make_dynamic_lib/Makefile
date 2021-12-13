# Makefile

RM = rm -f
CXX = g++
CXXFLAGS = -Wall -g
INCLUDE = -I./hello
LDFLAGS = -lhello
LDPATH = -L./hello

PROGS =	test1 test2

.PHONY: all
all: $(PROGS)
	@echo "build OK!"

clean:
	@$(RM) $(PROGS) *.o
	@echo "clean OK!"

%.o:%.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS) $(INCLUDE)

test1: test1.o
#	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)
#	$(CXX) -o $@ $^ -Wl,-R./hello $(LDFLAGS) $(LDPATH)
#	$(CXX) -o $@ $^ -Wl,-R./hello -Wl,--enable-new-dtags $(LDFLAGS) $(LDPATH)
	# 设置runpath为$ORGIN, 即相对于可执行程序的路径
	$(CXX) -o $@ $^ -Wl,-R'$$ORIGIN/hello' -Wl,--enable-new-dtags $(LDFLAGS) $(LDPATH)

test2: test2.o
	$(CXX) -o $@ $^ -ldl

