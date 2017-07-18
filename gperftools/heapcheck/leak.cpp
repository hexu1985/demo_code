#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

void leak()
{
	char *p = new char[1024*1024];
    p[0] = '1';
}

void no_leak()
{
	char *p = new char[1024*1024];
    p[0] = '1';
    delete [] p;
}

int main()
{
    printf("hello,world\n");
    leak();
    no_leak();
    return 0;
}
