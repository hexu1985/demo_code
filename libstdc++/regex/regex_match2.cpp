#include <regex>
#include <iostream>

int main(int argc, char *argv[])
{
    const char *regex_str = R"(\d+\.\d+\.\d+\.\d+)";
    if (argc != 2) {
        std::cout << "usage: " << argv[0] << " string" << std::endl;
        return -1;
    }

    std::cout << "regex: " << regex_str << std::endl;
    std::cout << "string: " << argv[1] << std::endl;

    if (std::regex_match(argv[1], std::regex(regex_str))) {
        std::cout << "string lieral matched\n";
    } else {
        std::cout << "string lieral not matched\n";
    }

    return 0;
}

