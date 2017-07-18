# Makefile

RM = rm -f
CXX = g++
CXXFLAGS = -Wall -g
INCLUDE = -I${GTESTROOT}/include
LDFLAGS = -lgtest
LDPATH = -L${GTESTROOT}/lib/.libs

PROGS = isprimetest isprimeparatest

.PHONY: all
all: $(PROGS)
	@echo "build OK!"

clean:
	@$(RM) $(PROGS) *.o
	@echo "clean OK!"

%.o:%.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS) $(INCLUDE)

# 一个最基本的例子
isprimetest: main.o isprime.o isprimetest.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)

#参数化的例子
isprimeparatest: main.o isprime.o isprimeparatest.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)
