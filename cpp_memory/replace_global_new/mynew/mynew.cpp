#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <new>

using namespace std;

class MyInit {
public:
    MyInit() {
        printf("MyInit::MyInit(): this is %p\n", (void *) this);
    } 

    ~MyInit() {
        printf("MyInit::~MyInit(): this is %p\n", (void *) this);
    }
};

static MyInit myInit;

__attribute__ ((visibility("default")))
void visible_func()
{
    printf("visible_func\n");
}

void func()
{
    printf("func\n");
}

__attribute__ ((visibility("hidden")))
void hidden_func()
{
    printf("hidden_func\n");
}

namespace {

void *operator_new_universal(size_t size) 
{
	void *pReturn = NULL;
	if (size == 0)
		size =1;	// 至少分配1字节

	while (1) {
		pReturn = malloc(size);
		if (pReturn != NULL) {
			return pReturn;
		}

        std::new_handler globalhandler = std::get_new_handler();	// 找到新的new_handler

		if (globalhandler) {
			(*globalhandler)();	// 如果内存不足了, 就调用new_handler
		} else {
			return NULL;
		}
	}
}

void operator_delete_universal(void *ptr)
{
    if (ptr == NULL)
        return;
    free(ptr);
}

} // namespace

void *operator new(std::size_t size)
{
	printf("my operator new %d bytes\n", (int) size);
    void *ptr = operator_new_universal(size);
    if (ptr == NULL) {
        throw std::bad_alloc();
    }
    return ptr;
}

void *operator new(std::size_t size, const std::nothrow_t& tag) noexcept
{
	printf("my operator new(nothrow) %d bytes\n", (int) size);
    void *ptr = operator_new_universal(size);
    return ptr;
}

void *operator new[](std::size_t size)
{
	printf("my operator new [] %d bytes\n", (int) size);
    void *ptr = operator_new_universal(size);
    if (ptr == NULL) {
        throw std::bad_alloc();
    }
    return ptr;
}

void *operator new[](std::size_t size, const std::nothrow_t& tag) noexcept
{
	printf("my operator new(nothrow) [] %d bytes\n", (int) size);
    void *ptr = operator_new_universal(size);
    return ptr;
}

void operator delete(void* ptr)
{
	printf("my operator delete\n");
    operator_delete_universal(ptr);
}

void operator delete(void* ptr, const std::nothrow_t& tag)
{
	printf("my operator delete(nothrow)\n");
    operator_delete_universal(ptr);
}

void operator delete [](void* ptr)
{
	printf("my operator delete []\n");
    operator_delete_universal(ptr);
}

void operator delete [](void* ptr, const std::nothrow_t& tag)
{
	printf("my operator delete(nothrow) []\n");
    operator_delete_universal(ptr);
}

