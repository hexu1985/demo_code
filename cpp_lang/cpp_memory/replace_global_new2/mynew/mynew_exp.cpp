#include "mynew.hpp"
#include <stdio.h>
#include <new>

using namespace std;

void *operator new(std::size_t size)
{
	printf("my operator new %d bytes\n", (int) size);
    void *ptr = my_operator_new_implement(size);
    if (ptr == NULL) {
        throw std::bad_alloc();
    }
    return ptr;
}

void *operator new(std::size_t size, const std::nothrow_t& tag) throw()
{
	printf("my operator new(nothrow) %d bytes\n", (int) size);
    void *ptr = my_operator_new_implement(size);
    return ptr;
}

void *operator new[](std::size_t size)
{
	printf("my operator new [] %d bytes\n", (int) size);
    void *ptr = my_operator_new_implement(size);
    if (ptr == NULL) {
        throw std::bad_alloc();
    }
    return ptr;
}

void *operator new[](std::size_t size, const std::nothrow_t& tag) throw()
{
	printf("my operator new(nothrow) [] %d bytes\n", (int) size);
    void *ptr = my_operator_new_implement(size);
    return ptr;
}

void operator delete(void* ptr)
{
	printf("my operator delete\n");
    my_operator_delete_implement(ptr);
}

void operator delete(void* ptr, const std::nothrow_t& tag)
{
	printf("my operator delete(nothrow)\n");
    my_operator_delete_implement(ptr);
}

void operator delete [](void* ptr)
{
	printf("my operator delete []\n");
    my_operator_delete_implement(ptr);
}

void operator delete [](void* ptr, const std::nothrow_t& tag)
{
	printf("my operator delete(nothrow) []\n");
    my_operator_delete_implement(ptr);
}

