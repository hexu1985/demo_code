
#include "hello.h"

#include <string>
#include <vector>

void test_hello()
{
#ifdef TEST_CRASH
	std::string a = "1234";
	(void) a;
	std::string b = a;
	(void) b;
	std::vector<std::string> c;
	c.push_back(a);
	c.push_back(std::move(b));
	(void) c;
#endif

	fprintf(stderr, "%s:%d, print_hello\n", __FILE__, __LINE__);
	print_hello();
	fprintf(stderr, "%s:%d\n", __FILE__, __LINE__);
}

