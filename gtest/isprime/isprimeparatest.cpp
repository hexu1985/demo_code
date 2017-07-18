
#include "isprimeparatest.h"
#include "isprime.h"

TEST_P(IsPrimeParamTest, HandleTrueReturn)
{
	int n = GetParam();
	EXPECT_TRUE(IsPrime(n));
}

INSTANTIATE_TEST_CASE_P(TrueReturn, IsPrimeParamTest, 
	testing::Values(3, 5, 11, 23, 17));
