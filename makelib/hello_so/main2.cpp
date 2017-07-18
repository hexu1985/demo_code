#include <dlfcn.h>
#include <iostream>

typedef int (*func_ptr) ();

using namespace std;

int main()
{
	const char *libso_name = "./libhello.so";

	// 打开动态库
	void *handle = dlopen(libso_name, RTLD_NOW);
	if (handle == NULL) {
		cout << "load " << libso_name << " error: " << dlerror() << endl;
		return -1;
	}

	// 从动态库中获取函数指针
	func_ptr print_hello;
	const char *func_name = "print_hello";
	print_hello = (func_ptr) dlsym(handle, func_name);
	if (print_hello == NULL) {
		cout << "get symbol " << func_name << " error: " << dlerror() << endl;
		return -1;
	}

	int ret = print_hello();

	// 关闭动态库
	dlclose(handle);

	return ret;
}
