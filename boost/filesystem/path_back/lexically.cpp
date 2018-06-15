#include <iostream>
#include "boost/filesystem.hpp"
#include <cassert>

namespace fs = boost::filesystem;

int main()
{
    std::cout << fs::path("foo/./bar/..").lexically_normal() << '\n'; // "foo/"
    std::cout << fs::path("foo/.///bar/../").lexically_normal() << '\n'; // "foo/";
    std::cout << fs::path("/a/d").lexically_relative("/a/b/c") << '\n'; // "../../d";
    std::cout << fs::path("/a/b/c").lexically_relative("/a/d") << '\n'; // "../b/c";
    std::cout << fs::path("a/b/c").lexically_relative("a") << '\n'; // "b/c";
    std::cout << fs::path("a/b/c").lexically_relative("a/b/c/x/y") << '\n'; // "../..";
    std::cout << fs::path("a/b/c").lexically_relative("a/b/c") << '\n'; // ".";
    std::cout << fs::path("a/b").lexically_relative("c/d") << '\n'; // "../../a/b";

    return 0;
}
