#include <gtest/gtest.h>
#include "foo.h"

TEST(FooTest, HandleNoneZeroInput)
{
	EXPECT_EQ(2, Foo(4, 10));
	EXPECT_EQ(6, Foo(30, 18));
}

TEST(FooTest, HandleZeroInput)
{
	EXPECT_ANY_THROW(Foo(10, 0));
}

