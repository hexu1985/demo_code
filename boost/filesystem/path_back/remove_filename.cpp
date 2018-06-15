#include <iostream>
#include "boost/filesystem.hpp"

namespace fs = boost::filesystem;

int main()
{
    std::cout << fs::path("foo/bar").remove_filename() << '\n'
            << fs::path("foo/").remove_filename() << '\n'
            << fs::path("/foo").remove_filename() << '\n'
            << fs::path("/").remove_filename() << '\n';
}
