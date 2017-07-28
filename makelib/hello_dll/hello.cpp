//#include <iostream>
#include <stdio.h>
#include <assert.h>

using namespace std;

extern "C" {

int print_hello()
{
//	cout << "hello world!" << endl;
    printf("hello world!\n");
	return 1;
}

}

