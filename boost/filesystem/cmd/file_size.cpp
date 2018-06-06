#include <iostream>
#include <fstream>
#include "boost/filesystem.hpp"

namespace fs = boost::filesystem;

int main()
{
    fs::path p = fs::current_path() / "example.bin";
    std::ofstream(p.string()).put('a'); // create file of size 1
    std::cout << "File size = " << fs::file_size(p) << '\n';
    fs::remove(p);
 
    try {
        fs::file_size("/dev"); // attempt to get size of a directory
    } catch(fs::filesystem_error& e) {
        std::cout << e.what() << '\n';
    }        
}

/**
File size = 1
filesystem error: cannot get file size: Is a directory [/dev]
*/
