#include <iostream>

using namespace std;

extern "C" {

void bye(const char *name)
{
	cout << "bye " << name << "!" << endl;
}

void bye_world()
{
	cout << "bye world!" << endl;
}

}
