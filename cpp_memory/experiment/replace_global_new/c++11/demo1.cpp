#include <stdio.h>
#include <stdlib.h>
#include <new>

using namespace std;

char *gPool = NULL;

void my_new_handler();

void *operator new(std::size_t size)
{
	void *pReturn = NULL;
	printf("my operator new\n");
	if (size == 0)
		size =1;	// 至少分配1字节

	while (1) {
		pReturn = malloc(size);
		if (pReturn != NULL) {
			printf("Got memory\n");
			return pReturn;
		}

		new_handler globalhandler = get_new_handler();	// 找到新的new_handler

		if (globalhandler) {
			printf("call new_handler...\n");
			(*globalhandler)();	// 如果内存不足了, 就调用new_handler
		} else {
			printf("no memory, no new_handler\n");
			throw std::bad_alloc();
		}
	}
}

void operator delete(void *p)
{
	printf("my operator delete\n");
	return free(p);
}

void *operator new [](std::size_t size)
{
	void *pReturn = NULL;
	printf("my operator new []\n");
	if (size == 0)
		size =1;	// 至少分配1字节

	while (1) {
		pReturn = malloc(size);
		if (pReturn != NULL) {
			printf("Got memory\n");
			return pReturn;
		}

		new_handler globalhandler = get_new_handler();	// 找到新的new_handler

		if (globalhandler) {
			printf("call new_handler...\n");
			(*globalhandler)();	// 如果内存不足了, 就调用new_handler
		} else {
			printf("no memory, no new_handler\n");
			throw std::bad_alloc();
		}
	}
}

void operator delete [](void *p)
{
	printf("my operator delete []\n");
	return free(p);
}

int main()
{
	gPool = new char[100*1024*1024];
	delete [] gPool;

	printf("Done.\n");
	return 0;
}

