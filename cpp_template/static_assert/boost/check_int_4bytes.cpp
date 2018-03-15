#include <boost/static_assert.hpp>
BOOST_STATIC_ASSERT_MSG(sizeof(int) == 4, "sizeof(int) should 4 bytes in This machine!");
int main() { return 0; }
