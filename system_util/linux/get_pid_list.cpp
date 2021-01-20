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

std::vector<uint64_t> get_pid_list()
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
      pid_list.push_back(pid);
    } catch (...) {
      std::cout << "invalid pid\n";
    }
	}
	closedir( dir ); /* 关闭目录 */
  return pid_list;
}

int main(void)
{
  auto pid_list = get_pid_list();
  std::cout << "pid: " << std::endl;
  for (auto pid: pid_list) {
    std::cout << pid << std::endl;
  }

	return 0;
}
