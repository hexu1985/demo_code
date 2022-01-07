#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <new>

using namespace std;

inline
void *operator new(std::size_t size)
{
	printf("inline my operator new in lib1\n");
	return malloc(size);
}

inline
void operator delete(void *p)
{
	printf("inline my operator delete in lib1\n");
	return free(p);
}

inline
void *operator new [](std::size_t size)
{
	printf("inline my operator new [] in lib1\n");
	return malloc(size);
}

inline
void operator delete [](void *p)
{
	printf("inline my operator delete [] lib1\n");
	return free(p);
}

