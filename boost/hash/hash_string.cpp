#include <iostream>
#include <string>
#include "boost/functional/hash.hpp"

int main(int argc, char *argv[])
{
    boost::hash<std::string> hash_func;
    for (int i = 1; i < argc; i++) {
        std::cout << "[" << i << "] " << argv[i] 
            << " --> " << hash_func(argv[i]) << std::endl;
    }

    return 0;
}
