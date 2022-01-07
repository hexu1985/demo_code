#include <boost/static_assert.hpp>
BOOST_STATIC_ASSERT_MSG(sizeof(int) == 8, "sizeof(int) should 8 bytes in This machine!");
int main() { return 0; }
