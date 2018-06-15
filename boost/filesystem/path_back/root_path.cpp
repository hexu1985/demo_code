#include <iostream>
#include "boost/filesystem.hpp"

namespace fs = boost::filesystem;

int main()
{
    std::cout << "Current root path is: " << fs::current_path().root_path() << '\n';
}
