#include <stdlib.h>
#include <iostream>
#include "md5.h"

int main(int argc, char *argv[])
{
    if (argc != 2) {
        std::cerr << "usage: " << argv[0] << " str\n";
        exit(1);
    }

    std::cout << MD5(argv[1]).toString() << std::endl;
    return 0;
}
