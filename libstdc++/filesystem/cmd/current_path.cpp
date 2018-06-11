#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

int main()
{
    std::cout << "Current path is " << fs::current_path() << '\n';
}

/*
Possible output:

Current path is "D:/local/ConsoleApplication1"
*/
