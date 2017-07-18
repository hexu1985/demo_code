# Makefile

RM = rm -f
CXX = g++
CXXFLAGS = -Wall -g
INCLUDE = -I${GTESTROOT}/include
LDFLAGS = -lgtest
LDPATH = -L${GTESTROOT}/lib/.libs

PROGS = footest stringcmptest predicateassertiontest assertfootest \
		fooenvironment footestsuite

.PHONY: all
all: $(PROGS)
	@echo "build OK!"

clean:
	@$(RM) $(PROGS) *.o
	@echo "clean OK!"

%.o:%.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS) $(INCLUDE)

# 一个最基本的例子
footest: main.o foo.o footest.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)

# 字符串检查
stringcmptest: main.o stringcmptest.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)

# 谓词断言
predicateassertiontest: main.o foo.o predicateassertiontest.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)

# 自定义断言的输出格式
assertfootest: main.o foo.o assertfootest.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)

# 类型检查断言, 注: 这个目标编译报错是正常的
typeassertiontest: main.o foo.o typeassertiontest.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)

# 全局事件例子
fooenvironment: main2.o foo.o footest.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)

# TestSuite事件和TestCase事件例子
footestsuite: main.o foo.o footest_f.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)
