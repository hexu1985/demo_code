// test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "hello.h"

using namespace std;
#pragma comment(lib,"hello.lib")  

int _tmain(int argc, _TCHAR* argv[])
{
	cout << "print_hello: " << print_hello() << endl;
	cout << "entry any key and enter to exit ";
	char c;
	cin >> c;
	return 0;
}

