#include "print.h"

int main()
{
	char *name = "world";
	Print print(name);
	print.hello();

	return 0;
}
