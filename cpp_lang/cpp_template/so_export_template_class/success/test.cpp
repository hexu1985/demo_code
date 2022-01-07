#include "hello.h"
#include "foo.h"
#include "mystring.h"

int main()
{
	print_hello();
  Foo<MyString> foo;
  foo.print();
	return 0;
}
