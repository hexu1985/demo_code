#include <linux/limits.h>
#include <unistd.h>
#include <iostream>

int main(int argc, char *argv[])
{
    char buf[PATH_MAX];
    for (int i = 1; i < argc; i++) {
        int n = readlink(argv[i], buf, PATH_MAX);
        if (n <= 0) {
            std::cout << "readlink error: " << argv[i] << std::endl;
        } else {
            std::string target(buf, n);
            std::cout << argv[i] << " --> " << target << std::endl;
        }
    }

    return 0;
}
