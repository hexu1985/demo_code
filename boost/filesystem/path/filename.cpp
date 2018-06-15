#include <iostream>
#include "boost/filesystem.hpp"

namespace fs = boost::filesystem;
 
int main()
{
    std::cout << fs::path("/foo/bar.txt").filename() << '\n'
              << fs::path("/foo/.bar").filename() << '\n'
              << fs::path("/foo/bar/").filename() << '\n'
              << fs::path("/foo/.").filename() << '\n'
              << fs::path("/foo/..").filename() << '\n'
              << fs::path(".").filename() << '\n'
              << fs::path("..").filename() << '\n'
              << fs::path("/").filename() << '\n'
              << fs::path("//host").filename() << '\n';
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
