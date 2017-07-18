#ifndef __base_h
#define __base_H

#include "base.h"
#include <string>

class Derived1: public Base {
public:
	// 构造函数
	Derived1();

	// 析构函数
	virtual ~Derived1();

	// 成员函数1
	virtual int foo(const std::string &);

	// 成员函数2
	virtual void print();
};

#endif

