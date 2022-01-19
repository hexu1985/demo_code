#include <stdlib.h>
#include <iostream>

int main(int argc, char *argv[]) 
{
    char *ts_val = nullptr;
    ts_val = getenv("TZ");
    if (ts_val) {
        std::cout << "TZ: " << ts_val << std::endl;
    } else {
        std::cout << "TZ not set" << std::endl;
    }

    setenv("TZ", "Asia/Shanghai", 1);

    std::cout << "after setenv" << std::endl;
    ts_val = getenv("TZ");
    if (ts_val) {
        std::cout << "TZ: " << ts_val << std::endl;
    } else {
        std::cout << "TZ not set" << std::endl;
    }

    char *save = ts_val;
    setenv("TZ", "America/NewYork", 1);
    ts_val = getenv("TZ");
    if (ts_val) {
        std::cout << "TZ: " << ts_val << std::endl;
    } else {
        std::cout << "TZ not set" << std::endl;
    }

    std::cout << "save: " << save << std::endl;

    return 0;
}
