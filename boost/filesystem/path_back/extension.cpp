#include <iostream>
#include "boost/filesystem.hpp"

namespace fs = boost::filesystem;

int main()
{
    std::cout << fs::path("/foo/bar.txt").extension() << '\n'
            << fs::path("/foo/bar.").extension() << '\n'
            << fs::path("/foo/bar").extension() << '\n'
            << fs::path("/foo/bar.txt/bar.cc").extension() << '\n'
            << fs::path("/foo/bar.txt/bar.").extension() << '\n'
            << fs::path("/foo/bar.txt/bar").extension() << '\n'
            << fs::path("/foo/.").extension() << '\n'
            << fs::path("/foo/..").extension() << '\n'
            << fs::path("/foo/.hidden").extension() << '\n'
            << fs::path("/foo/..bar").extension() << '\n';
    return 0;
}
