#include <stdio.h>
#include <new>

using namespace std;

class Simple_class {
public:
	int m_value;

	static void *operator new(size_t n);
	static void *operator new(std::size_t n, char *file, int line);
};

void *Simple_class::operator new(std::size_t n, char *file, int line)
{
	printf("size: %d\nnew at %s, %d\n", n, file, line);
	return ::operator new(n);
}

void *Simple_class::operator new(size_t n)
{
	printf("size: %d\n", n);
	return ::operator new(n);
}

class Derived_class: public Simple_class {
public:
	int m_derived_value;
};

int main()
{
	Simple_class *p1 = new Simple_class();
	Derived_class *p2 = new(__FILE__, __LINE__) Derived_class();
	char *buffer = new char[10];

	return 0;
}
