#include <regex>
#include <iostream>

int main(int argc, char *argv[])
{
    if (argc != 3) {
        std::cout << "usage: " << argv[0] << " regex string" << std::endl;
        return -1;
    }

    std::cout << "regex: " << argv[1] << std::endl;
    std::cout << "string: " << argv[2] << std::endl;

    if (std::regex_match(argv[2], std::regex(argv[1]))) {
        std::cout << "string lieral matched\n";
    } else {
        std::cout << "string lieral not matched\n";
    }

    return 0;
}

