#include <stdio.h>
#include <stdlib.h>
#include <new>

using namespace std;

int main()
{
	char *pool = new char[100*1024*1024];
	delete [] pool;

	printf("Done.\n");
	return 0;
}

