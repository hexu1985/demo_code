#include <string>
#include <iostream>
#include "load_file.hpp"

int main(int argc, char *argv[]) 
{
    const char *path = "/sys/devices/virtual/dmi/id/sys_vendor";
    std::string sys_vendor = load_file_first_line(path);
    std::cout << "sys_vendor: " << sys_vendor << std::endl;
    return 0;
}

