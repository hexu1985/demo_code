#include <stdlib.h>
#include <iostream>

#ifndef VALUE
#define VALUE "hello"
#endif

int main(int argc, char *argv[])
{
    const char *name = "TEST";
    if (setenv(name, VALUE, 1) < 0) {
        std::cout << "setenv " << name << "=" << VALUE << ", failed!" << std::endl;
        exit(1);
    }

    char *value = getenv(name);
    if (value == NULL) {
        std::cout << "env var: " << name << " is not set" << std::endl;
    } else {
        std::cout << "env var: " << name << "=" << value << std::endl;
    }

    return 0;
}
