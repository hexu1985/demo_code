#include <stdio.h>
#include <stdlib.h>
#include <new>
#include <vector>

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

		new_handler globalhandler = set_new_handler(0);	// 找到新的new_handler
		set_new_handler(globalhandler);

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

		new_handler globalhandler = set_new_handler(0);	// 找到新的new_handler
		set_new_handler(globalhandler);

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
    std::vector<int> vec(5);

	printf("Done.\n");
	return 0;
}

