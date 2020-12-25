#include <iostream>
#include <fstream>
#include <string>
#include <regex>

int main(int argc, char *argv[]) 
{
    std::ifstream meminfo("/proc/cpuinfo");
    if (!meminfo) {
        std::cout << "open /proc/cpuinfo fail!" << std::endl;
        return 0;
    }

    std::string line;
    std::regex rgx("^cpu cores.*:.*([0-9]+).*$");
    while (std::getline(meminfo, line)) {
        if (std::regex_match(line, rgx)) {
            std::cout << line << std::endl;
        }
        std::smatch sm;    // same as std::match_results<string::const_iterator> sm;
        if (std::regex_match (line, sm, rgx)) {
            std::cout << sm.size() << std::endl;
            for (int i = 0; i < sm.size(); i++) {
                std::cout << i << ". " << sm[i] << std::endl;
            }
        }
    }

    return 0;
}
