#include <iostream>
#include "boost/filesystem.hpp"

namespace fs = boost::filesystem;

int main()
{
    fs::path p = "C:\\users\\abcdef\\AppData\\Local\\Temp\\";
    std::cout << "Examining the path " << p << " through iterators gives\n";
    for(auto& e : p)
        std::cout << e << '\n';
}
