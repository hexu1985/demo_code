#include <linux/limits.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <string>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <fstream>

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

std::vector<std::string> get_args_by_pid(uint64_t pid)
{
    std::string cmdline_file = "/proc/"+std::to_string(pid)+"/cmdline";

    std::ifstream ifile(cmdline_file);
    if (!ifile) {
        std::cout << "open file: " << cmdline_file << " failed!" << std::endl;
        exit(1);
    }

    std::string line;
    if (!std::getline(ifile, line)) {
        std::cout << "read file: " << cmdline_file << " failed!" << std::endl;
    }
    std::vector<std::string> vec;
    split(line, '\0', vec);
    if (vec.back().empty())
        vec.pop_back();

    return vec;
}

std::string get_cwd_by_pid(uint64_t pid)
{
    char buf[PATH_MAX];
    std::string cwd_file = "/proc/"+std::to_string(pid)+"/cwd";
    int n = readlink(cwd_file.c_str(), buf, PATH_MAX);
    if (n <= 0) {
        std::cout << "readlink error: " << cwd_file << std::endl;
        return std::string{};
    } else {
        std::string target(buf, n);
        std::cout << cwd_file << " --> " << target << std::endl;
        return target;
    }
}

std::string get_exe_by_pid(uint64_t pid)
{
    char buf[PATH_MAX];
    std::string exe_file = "/proc/"+std::to_string(pid)+"/exe";
    int n = readlink(exe_file.c_str(), buf, PATH_MAX);
    if (n <= 0) {
        std::cout << "readlink error: " << exe_file << std::endl;
        return std::string{};
    } else {
        std::string target(buf, n);
        std::cout << exe_file << " --> " << target << std::endl;
        return target;
    }
}

int main(int argc, char *argv[])
{
    bool reboot_myself = true;
    pid_t pid = getpid();
    if (argc == 2) {
        pid = std::stoul(argv[1]);
        reboot_myself = false;
    }
    
    std::cout << "pid: " << pid << std::endl;
    auto args = get_args_by_pid(pid);
    std::ostream_iterator<std::string> out_it (std::cout,", ");
    std::copy(args.begin(), args.end(), out_it);

    std::cout << std::endl;

    std::string cwd = get_cwd_by_pid(pid);
    std::string exe = get_exe_by_pid(pid);

    pid_t child_pid = fork();
    if (child_pid > 0) {
        kill(pid, SIGINT);
        exit(0);
    } else if (child_pid == 0) { // child
        if (!reboot_myself) {
            if (chdir(cwd.c_str()) < 0) {
                std::cout << "chdir error: " << cwd << std::endl;
                exit(1);
            }
        } else {
            if (0 == access("/tmp/test_reboot", R_OK)) {
                unlink("/tmp/test_reboot");
            } else {
                exit(0);
            }
            for (int i = 3; i < 1024; i++) {
                close(i);
            }
        }
        std::vector<char *> exe_argv;
#if 0
        for (int i = 0; i < args.size(); i++) {
            exe_argv.push_back(const_cast<char *>(args[i].c_str()));
        }
#else
        for (auto &arg: args) {
            exe_argv.push_back(const_cast<char *>(arg.c_str()));
        }
#endif
        exe_argv.push_back(NULL);
        execv(exe.c_str(), exe_argv.data());
    } else { // error
        std::cout << "fork failed!" << std::endl;
        exit(1);
    }

    return 0;
}
