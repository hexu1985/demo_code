#include "Poco/SharedLibrary.h"
#include <iostream>

using namespace std;

typedef int (*func_ptr) (int, int);

int main(int argc, char *argv[])
{
	const char *libso_name = "./dlldemo1.dll";
    if (argc == 2)
        libso_name = argv[1];

	// 打开动态库
    Poco::SharedLibrary lib(libso_name);

	// 从动态库中获取函数指针
	const char *func_name = "Add";
	func_ptr my_add = (func_ptr) lib.getSymbol(func_name);

	int ret = my_add(3, 5);
    cout << "3+5=" << ret << endl;

	// 关闭动态库
    lib.unload();

	return ret;
}

