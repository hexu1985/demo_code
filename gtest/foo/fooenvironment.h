#ifndef __fooenvironment_h 
#define __fooenvironment_h 

#include <iostream>

class FooEnvironment : public testing::Environment
{
public:
	virtual void SetUp()
	{
		std::cout << "Foo FooEnvironment SetUp" << std::endl;
	}
	virtual void TearDown()
	{
		std::cout << "Foo FooEnvironment TearDown" << std::endl;
	}
};

#endif
