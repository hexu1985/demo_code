#include <gtest/gtest.h>
#include "foo.h"

testing::AssertionResult AssertFoo(const char *m_expr, const char *n_expr,
		const char *k_expr, int m, int n, int k)
{
	if (Foo(m, n) == k)
		return testing::AssertionSuccess();
	testing::Message msg;

	msg << m_expr << " 和 " << n_expr << " 的最大公约数应该是: "
		<< Foo(m, n) << " 而不是: " << k_expr;
	return testing::AssertionFailure(msg);
}

TEST(AssertFooTest, HandleFail)
{
	EXPECT_PRED_FORMAT3(AssertFoo, 3, 6, 2);
}
	

	
