#include <iostream>
#include "boost/filesystem.hpp"

namespace fs = boost::filesystem;

int main()
{
    std::cout << "Current path is " << fs::current_path() << '\n';
}

/*
Possible output:

Current path is "D:/local/ConsoleApplication1"
*/
