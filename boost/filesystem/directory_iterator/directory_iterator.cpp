#include <fstream>
#include <iostream>
#include "boost/filesystem.hpp"

namespace fs = boost::filesystem;
 
int main()
{
    fs::create_directories("sandbox/a/b");
    std::ofstream("sandbox/file1.txt");
    std::ofstream("sandbox/file2.txt");
    for(auto& p: fs::directory_iterator("sandbox"))
        std::cout << p << '\n';
    fs::remove_all("sandbox");
}

/*
Possible output:

"sandbox/a"
"sandbox/file1.txt"
"sandbox/file2.txt"
*/
