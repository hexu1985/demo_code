# Makefile

RM = rm -f
CXX = /opt/android-ndk-r16b/android-aarch64/bin/aarch64-linux-android-clang++
CXXFLAGS = -std=c++11 -fPIC -Wall -g -DNDEBUG -fPIE -DTEST_CRASH
INCLUDE = -I./hello
LDFLAGS = -pie -lhello 
LDPATH = -L./hello

PROGS =	main 

.PHONY: all
all: $(PROGS)
	@echo "build OK!"

clean:
	@$(RM) $(PROGS) *.o
	@echo "clean OK!"

%.o:%.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS) $(INCLUDE)

main: main.o test_hello.o
#	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)
#	$(CXX) -o $@ $^ -Wl,-R./hello $(LDFLAGS) $(LDPATH)
	$(CXX) -o $@ $^ -Wl,-R./hello -Wl,--enable-new-dtags $(LDFLAGS) $(LDPATH)

