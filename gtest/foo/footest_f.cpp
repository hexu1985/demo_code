#include <gtest/gtest.h>
#include "foo.h"
#include "footest.h"

std::string *FooTest::shared_resource_ = NULL;

int FooTest::count = 0;

TEST_F(FooTest, HandleNoneZeroInput)
{
	EXPECT_EQ(2, Foo(4, 10));
	EXPECT_EQ(6, Foo(30, 18));
	std::cout << "HandleNoneZeroInput: " << count << std::endl;
}

TEST_F(FooTest, HandleZeroInput)
{
	EXPECT_ANY_THROW(Foo(10, 0));
	std::cout << "HandleZeroInput: " << count << std::endl;
}

