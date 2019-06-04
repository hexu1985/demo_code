#include <stdio.h>
#include <stdlib.h>
#include <new>

using namespace std;

class Simple_class {
public:
	int m_value;

	static void *operator new(size_t size);
    static void operator delete(void *rawMemory, std::size_t size);
};

void *Simple_class::operator new(size_t size)
{
	printf("Simple_class::operator new, size: %d\n", (int) size);
	return malloc(size);
}

void Simple_class::operator delete(void *rawMemory, std::size_t size)
{
	printf("Simple_class::operator delete, size: %d\n", (int) size);
    free(rawMemory);
}

void *operator new(std::size_t size)
{
	void *pReturn = NULL;
	printf("my operator new\n");
	if (size == 0)
		size =1;	// 至少分配1字节

    pReturn = malloc(size);
    if (pReturn != NULL) {
        printf("Got memory\n");
        return pReturn;
    } else {
        printf("no memory, no new_handler\n");
        throw std::bad_alloc();
    }
}

void operator delete(void *p)
{
	printf("my operator delete\n");
	return free(p);
}

int main()
{
	Simple_class *p1 = new Simple_class();
	char *buffer = new char[10];

    delete p1;
    delete [] buffer;

	return 0;
}
