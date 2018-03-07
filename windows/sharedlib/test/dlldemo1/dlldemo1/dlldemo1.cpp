// dlldemo1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <windows.h>
#include <iostream>

using namespace std;
#pragma comment(lib, "..\\debug\\DLLDemo1.lib")

extern "C" _declspec(dllimport) int Add(int a, int b);

int main(int argc, char *argv[])
{
	cout << Add(2, 3) << endl;
	return 0;
}