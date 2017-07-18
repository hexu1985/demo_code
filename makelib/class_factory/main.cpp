#include "base.h"
#include <dlfcn.h>
#include <assert.h>
#include <iostream>

typedef Base *(*create_func_ptr) ();
typedef void (*destroy_func_ptr) (Base *);

using namespace std;

void test_so(const char *libso_name)
{
	// 打开动态库1
	void *handle = dlopen(libso_name, RTLD_NOW);
	if (handle == NULL) {
		cout << "load " << libso_name << " error: " << dlerror() << endl;
		return;
	}

	// 从动态库中获取函数指针
	create_func_ptr create_func;
	create_func = (create_func_ptr) dlsym(handle, "create");
	if (create_func == NULL) {
		cout << "get symbol create error: " << dlerror() << endl;
		return;
	}

	Base *base = create_func();
	assert(base);
	base->foo("test foo");
	base->print();

	destroy_func_ptr destroy_func;
	destroy_func = (destroy_func_ptr) dlsym(handle, "destroy");
	if (destroy_func == NULL) {
		cout << "get symbol destroy error: " << dlerror() << endl;
	} else {
		destroy_func(base);
	}

	// 关闭动态库
	dlclose(handle);
}

int main()
{
	test_so("./libderived1.so");
	test_so("./libderived2.so");

	return 0;
}
