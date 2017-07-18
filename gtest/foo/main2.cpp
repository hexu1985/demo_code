#include <gtest/gtest.h>
#include "fooenvironment.h"

int main(int argc, char *argv[])
{
	testing::AddGlobalTestEnvironment(new FooEnvironment);
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

