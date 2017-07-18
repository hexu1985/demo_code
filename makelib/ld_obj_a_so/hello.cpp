#include <iostream>

using namespace std;

extern "C" {

void hello(const char *name)
{
	cout << "hello " << name << "!" << endl;
}

void hello_world()
{
	cout << "hello world!" << endl;
}

}
