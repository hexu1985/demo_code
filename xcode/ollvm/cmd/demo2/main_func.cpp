#include <stdlib.h>

#ifdef USE_BCF_OPT
unsigned int target_function(unsigned int n) __attribute((__annotate__(("bcf"))));
#endif

#ifdef USE_FLA_OPT
unsigned int target_function(unsigned int n) __attribute((__annotate__(("fla"))));
#endif

#ifdef USE_SUB_OPT
unsigned int target_function(unsigned int n) __attribute((__annotate__(("sub"))));
#endif

unsigned int target_function(unsigned int n) 
{
	unsigned int mod = n % 4;
	unsigned int result = 0;
	if (mod == 0) result = (n | 0xBAAAD0BF) * (2 ^ n);
	else if (mod == 1) result = (n & 0xBAAAD0BF) * (3 + n);
	else if (mod == 2) result = (n ^ 0xBAAAD0BF) * (4 | n);
	else result = (n + 0xBAAAD0BF) * (5 & n);
	return result;
}

int main(int argc, char *argv[])
{
	int a = atoi(argv[1]);
	return target_function(a);
}
