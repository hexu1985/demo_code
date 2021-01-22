#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

bool startswith(const std::string& str, const std::string &prefix) {
    return str.compare(0, prefix.length(), prefix) == 0;
}

void split(const std::string& s, char c,
        std::vector<std::string>& v) {
    std::string::size_type i = 0;
    std::string::size_type j = s.find(c);

    while (j != std::string::npos) {
        v.push_back(s.substr(i, j-i));
        i = ++j;
        j = s.find(c, j);

        if (j == std::string::npos)
            v.push_back(s.substr(i, s.length( )));
    }
}

bool has_debugger()
{
    auto pid = getpid();
    std::string status_path = "/proc/"+std::to_string(pid)+"/status";

    std::ifstream ifile(status_path);
    if (!ifile) {
        std::cout << "open file: " << status_path << " failed!" << std::endl;
        exit(1);
    }

    std::string line;
    while (std::getline(ifile, line)) {
        if (!startswith(line, "TracerPid")) {
            continue;
        }
        std::vector<std::string> vec;
        split(line, ':', vec);
        auto tracer_pid = std::stol(vec[1]);
        if (tracer_pid) {
            return true;
        } else {
            return false;
        }
    }

    std::cout << "no found TracerPid field";
    exit(1);
}


int main()
{
    auto pid = getpid();
    std::cout << "my pid: " << pid << std::endl;

    bool current_state = has_debugger();
    std::cout << (current_state ? "has debugger!" : "no debugger!") << std::endl;

    bool last_state = current_state;

    while (true) {
        sleep(1);
        current_state = has_debugger();
        if (current_state == last_state) {
            continue;
        }
        std::cout << (current_state ? "has debugger!" : "no debugger!") << std::endl;
        last_state = current_state;
    }

    return 0;
}
