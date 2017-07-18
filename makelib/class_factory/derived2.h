#ifndef __base_h
#define __base_H

#include "base.h"
#include <string>

class Derived2: public Base {
public:
	// 构造函数
	Derived2();

	// 析构函数
	virtual ~Derived2();

	// 成员函数1
	virtual int foo(const std::string &);

	// 成员函数2
	virtual void print();
};

#endif

