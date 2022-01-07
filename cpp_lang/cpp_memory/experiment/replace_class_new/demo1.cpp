#include <stdio.h>
#include <new>

using namespace std;

class Simple_class {
public:
	int m_value;

	static void *operator new(size_t size);
    static void operator delete(void *rawMemory, std::size_t size);
};

void *Simple_class::operator new(size_t size)
{
	printf("Simple_class::operator new, size: %d\n", (int) size);
	return ::operator new(size);
}

void Simple_class::operator delete(void *rawMemory, std::size_t size)
{
	printf("Simple_class::operator delete, size: %d\n", (int) size);
    ::operator delete(rawMemory);
}


class Derived_class: public Simple_class {
public:
	int m_derived_value;
};

int main()
{
	Simple_class *p1 = new Simple_class();
	Derived_class *p2 = new Derived_class();
	char *buffer = new char[10];

    delete p1;
    delete p2;
    delete [] buffer;

	return 0;
}
