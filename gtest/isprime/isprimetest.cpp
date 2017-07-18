#include <gtest/gtest.h>
#include "isprime.h"

TEST(IsPrimeTest, HandleTrueReturn)
{
	EXPECT_TRUE(IsPrime(3));
	EXPECT_TRUE(IsPrime(5));
	EXPECT_TRUE(IsPrime(11));
	EXPECT_TRUE(IsPrime(23));
	EXPECT_TRUE(IsPrime(17));
}
