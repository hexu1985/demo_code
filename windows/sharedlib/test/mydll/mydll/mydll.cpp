// mydll.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "..\\Debug\\mydll.h"  

#pragma comment(lib, "..\\Debug\\mydll.lib")

int _tmain(int argc, _TCHAR* argv[])
{
	func();
	return 0;
}
