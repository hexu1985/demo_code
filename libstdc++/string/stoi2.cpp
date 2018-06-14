// stoi example
#include <iostream>   // std::cout
#include <string>     // std::string, std::stoi

int main (int argc, char *argv[])
{
    std::string::size_type sz;   // alias of size_t

    for (int i = 1; i < argc; i++)
        std::cout << std::stoi(argv[i], &sz) << std::endl;

    return 0;
}

