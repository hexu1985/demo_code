#include <iostream>
#include <string.h>

int main()
{
    for (int i = 0; i < 255; i++) {
        std::cout << "errno(" << i << "): " << strerror(i) << std::endl;
    }

    return 0;
}
