#include <stdlib.h>
#include <iostream>

int main(int argc, char *argv[])
{
    if (argc != 3) {
        std::cout << "usage: " << argv[0] << " name value" << std::endl;
        exit(1);
    }

    if (setenv(argv[1], argv[2], 1) < 0) {
        std::cout << "setenv " << argv[1] << "=" << argv[2] << ", failed!" << std::endl;
        exit(1);
    }

    char *value = getenv(argv[1]);
    if (value == NULL) {
        std::cout << "env var: " << argv[1] << " is not set" << std::endl;
    } else {
        std::cout << "env var: " << argv[1] << "=" << value << std::endl;
    }

    return 0;
}
