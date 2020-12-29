#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <set>

int main(int argc, char *argv[]) 
{
    std::ifstream meminfo("/proc/cpuinfo");
    if (!meminfo) {
        std::cout << "open /proc/cpuinfo fail!" << std::endl;
        return 0;
    }

    std::string line;
    std::regex rgx("^physical id.*$");
    std::set<std::string> cpu_set;
    while (std::getline(meminfo, line)) {
        if (std::regex_match(line, rgx)) {
            std::cout << line << std::endl;
            cpu_set.insert(line);
        }
    }
    std::cout << "physical cpu count: " << cpu_set.size() << std::endl;


    return 0;
}

