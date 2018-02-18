CREATE_SO = g++ -shared -static -Wl,--kill-at
RM = rm -f
CXX = g++
CXXFLAGS = -Wall -fPIC -O2 -c #-DNDEBUG
TARGETS = hello
LIB_OBJS = hello.o
DLL_NAME = hello.dll
LIB_NAME = libhello.a
DEF_NAME = hello.def

.PHONY: all
all: $(TARGETS)
	@echo "build OK!"

.PHONY: clean
clean:
	$(RM) $(TARGETS) *.o *.dll *.lib *.def *.a *.exp

$(LIB_NAME): $(LIB_OBJS)
	$(CREATE_SO) $(LIB_OBJS) -o $(DLL_NAME) -Wl,--output-def,$(DEF_NAME),--out-implib,$(LIB_NAME)

$(LIB_OBJS):%.o: %.cpp
	$(CXX) $(CXXFLAGS) -DBULID_DLL $^

main.o: main.cpp
	$(CXX) $(CXXFLAGS) $^

hello: main.o $(LIB_NAME)
	$(CXX) -o $@ $^

