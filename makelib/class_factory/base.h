#ifndef __base_h
#define __base_H

#include <string>

class Base {
public:
	// 构造函数
	Base();

	// 析构函数
	virtual ~Base() = 0;

	// 成员函数1
	virtual int foo(const std::string &) = 0;

	// 成员函数2
	virtual void print() = 0;
};

extern "C" Base *create();
extern "C" void destroy(Base *);

#endif
