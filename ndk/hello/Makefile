# Makefile

RM = rm -f
CXX = /opt/android-ndk-r16b-clang/android-aarch64/bin/clang++
CXXFLAGS = -Wall -g -fPIE -pie
INCLUDE = 
LDFLAGS = 
LDPATH = 

PROGS =	hello hello_static

.PHONY: all
all: $(PROGS)
	@echo "build OK!"

clean:
	@$(RM) $(PROGS) *.o
	@echo "clean OK!"

%.o:%.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS) $(INCLUDE)

hello: hello.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)

hello_static: hello.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH) -static-libstdc++

