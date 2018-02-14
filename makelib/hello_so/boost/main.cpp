#include <iostream>
#include <boost/function.hpp>
#include <boost/dll.hpp>

using namespace std;

int main()
{
	const char *libso_name = "../libhello.so";

	// 打开动态库
    boost::dll::shared_library lib(libso_name);

	// 从动态库中获取函数指针
	const char *func_name = "print_hello";
    boost::function<int()> print_hello = lib.get<int()>(func_name);

	int ret = print_hello();

	// 关闭动态库

	return ret;
}

