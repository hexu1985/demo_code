#include "Poco/SharedLibrary.h"
#include <iostream>

using namespace std;

typedef int (*func_ptr) ();

int main()
{
	const char *libso_name = "../libhello.so";

	// 打开动态库
    Poco::SharedLibrary lib(libso_name);

	// 从动态库中获取函数指针
	const char *func_name = "print_hello";
	func_ptr print_hello = (func_ptr) lib.getSymbol(func_name);

	int ret = print_hello();

	// 关闭动态库
    lib.unload();

	return ret;
}

