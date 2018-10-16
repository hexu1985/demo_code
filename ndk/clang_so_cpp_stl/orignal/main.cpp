#include <cstdio>

void test_hello();

        
int main(int argc, char* argv[]) {

	printf("hello 10.16.11.05\n");

	int gtest_re = 0;
	test_hello();

	printf("bye 10.16.11.05\n");

	return gtest_re;
}
