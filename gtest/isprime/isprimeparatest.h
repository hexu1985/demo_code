#ifndef	__isprimeparatest_h
#define	__isprimeparatest_h

#include <gtest/gtest.h>

class IsPrimeParamTest : public::testing::TestWithParam<int>
{
};

#endif

