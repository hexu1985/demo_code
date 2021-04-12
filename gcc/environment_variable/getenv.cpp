#include <stdlib.h>
#include <iostream>

int main(int argc, char *argv[])
{
    for (int i = 1; i < argc; i++) {
        char *value = getenv(argv[i]);
        if (value == NULL) {
            std::cout << "env var: " << argv[i] << " is not set" << std::endl;
        } else {
            std::cout << "env var: " << argv[i] << "=" << value << std::endl;
        }
    }
}
