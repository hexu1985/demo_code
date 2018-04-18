#include <iostream>
#include "boost/filesystem.hpp"
namespace fs = boost::filesystem;
 
int main()
{
    std::cout << "Current root name is: " << fs::current_path().root_name() << '\n';
}
