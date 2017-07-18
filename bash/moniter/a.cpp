#include <iostream>
#include <unistd.h>

int main()
{
    while (true) {
        std::cout << "hello" << std::endl;
        sleep(1);
    }
    char a;
    std::cin >> a;
    return 0;
}
