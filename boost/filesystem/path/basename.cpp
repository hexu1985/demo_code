#include <iostream>
#include "basename.h"
 
int main()
{
    std::cout << basename("/foo/bar.txt") << '\n'
              << basename("/foo/.bar") << '\n'
              << basename("/foo/bar/") << '\n'
              << basename("/foo/.") << '\n'
              << basename("/foo/..") << '\n'
              << basename(".") << '\n'
              << basename("..") << '\n'
              << basename("/") << '\n'
              << basename("//host") << '\n';
}

/*
Possible output:

"bar.txt"
".bar"
""
"."
".."
"."
".."
""
"host"
*/
