#include "lib1.hpp"
#include "lib2.hpp"
#include <stdio.h>
#include <string>
#include <vector>

void my_func() {
    printf("my_func begin\n");
    char *p = new char[40];
    delete [] p;
//    printf("my_func middle\n");
//    std::vector<int> *vec = new std::vector<int>(100);
//    delete vec;
    printf("my_func end\n");
}

int main()
{
    printf("before my_func\n");
    my_func();
    printf("after my_func\n");

    printf("before lib1::foo\n");
    lib1::foo();
    printf("after lib1::foo\n");

    printf("before lib2::bar\n");
    lib2::bar();
    printf("after lib2::bar\n");
    return 0;
}

