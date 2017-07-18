#ifndef __footest_h
#define __footest_h

#include <iostream>
#include <string>
#include <gtest/gtest.h>

class FooTest: public testing::Test {
protected:
	static void SetUpTestCase()
	{
		std::cout << "Foo FooTest SetUpTestCase" << std::endl;
		shared_resource_ = new std::string("FooTest");
	}

	static void TearDownTestCase()
	{
		std::cout << "Foo FooTest TearDownTestCase" << std::endl;
		delete shared_resource_;
		shared_resource_ = NULL;
	}

	// Some Expensive resource shared by all tests.
	static std::string *shared_resource_;

	//-------------------------------------------------------------
	virtual void SetUp()
	{
		count++;
		std::cout << "Foo FooTest SetUp: " << count << std::endl;
	}

	virtual void TearDown()
	{
		std::cout << "Foo FooTest TearDown: " << count << std::endl;
	}

	static int count;
};

#endif
