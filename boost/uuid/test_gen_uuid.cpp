#include "gen_uuid.h"
#include <iostream>

int main()
{
    for (int i = 0; i < 5; i++) {
        std::cout << "uuid: " << gen_uuid() << std::endl;
    }

    return 0;
}

