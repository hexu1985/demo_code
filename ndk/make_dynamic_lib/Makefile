# Makefile

RM = rm -f
CXX = /opt/android-ndk-r16b-clang/android-aarch64/bin/aarch64-linux-android-clang++
CXXFLAGS = -fPIC -Wall -g -DNDEBUG -fPIE
INCLUDE = -I./hello
LDFLAGS = -pie -lhello
LDPATH = -L./hello

PROGS =	test1 test2 test1_with_cxx_lib

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
	$(CXX) -o $@ $^ -Wl,-R./hello -Wl,--enable-new-dtags $(LDFLAGS) $(LDPATH)

test2: test2.o
	$(CXX) -o $@ $^ -pie -ldl

test1_with_cxx_lib: test1.o
	$(CXX) -o $@ $^ -Wl,-R./hello -Wl,--enable-new-dtags -pie -lhello_with_cxx_lib -L./hello -static-libstdc++ 

