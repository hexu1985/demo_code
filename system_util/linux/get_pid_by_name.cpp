#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>
#define MAX 1024
#define PATH_SIZE 128

#include <vector>
#include <string>
#include <iostream>
#include <fstream>

#include "string_trim.hpp"

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

std::string get_name_by_pid(uint64_t pid)
{
    std::string status_path = "/proc/"+std::to_string(pid)+"/status";

    std::ifstream ifile(status_path);
    if (!ifile) {
        std::cout << "open file: " << status_path << " failed!" << std::endl;
        exit(1);
    }

    std::string line;
    while (std::getline(ifile, line)) {
        if (!startswith(line, "Name")) {
            continue;
        }
        std::vector<std::string> vec;
        split(line, ':', vec);
        return trim_copy(vec[1]);
    }

    std::cout << "no found TracerPid field";
    exit(1);
}

std::vector<uint64_t> get_pid_list_by_name(const std::string &process_name)
{
  std::vector<uint64_t> pid_list;
	DIR *dir;
	struct dirent *entry;
	if((dir = opendir( "/proc" )) == NULL ) { /* 打开/proc目录 */
		perror("fail to open dir");
			return pid_list;
	}
	while((entry = readdir( dir ) ) != NULL){
		if(entry->d_name[0] == '.') /* 跳过当前目录，proc目录没有父目录 */ 
			continue;
		/* 跳过系统信息目录，所有进程的目录全都是数字，而系统信息目录全都不是数字 */
		if( (entry->d_name[0] <='0' ) || (entry->d_name[0] >= '9'))
			continue;
    try {
      auto pid = std::stoull(entry->d_name);
      auto name = get_name_by_pid(pid);
      if (name == process_name)
        pid_list.push_back(pid);
    } catch (...) {
      std::cout << "invalid pid\n";
    }
	}
	closedir( dir ); /* 关闭目录 */
  return pid_list;
}

int main(int argc, char *argv[])
{
  if (argc != 2) {
    std::cout << "usage: " << argv[0] << "process_name" << std::endl;
    exit(1);
  }

  auto pid_list = get_pid_list_by_name(argv[1]);
  std::cout << "pid: " << std::endl;
  for (auto pid: pid_list) {
    std::cout << pid << std::endl;
  }

	return 0;
}
