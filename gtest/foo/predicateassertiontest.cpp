#include <gtest/gtest.h>
#include "foo.h"

bool MutuallyPrime(int m, int n)
{
	return Foo(m, n) < 1;
}

TEST(PredicateAssertionTest, Demo)
{
	int m = 5, n = 6;
	EXPECT_PRED2(MutuallyPrime, m, n);
}

