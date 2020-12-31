#include <stdio.h>
#include <sys/vfs.h>
#include <errno.h>
#include <string.h>
#include <string>
#include <iostream>

int main(int argc, char *argv[])
{
	  const char *path = "/home";
		if (argc > 1)
				path = argv[1];

    struct statfs sfs;
    int ret = statfs(path, &sfs);
		if (ret < 0) {
				printf("statfs error: %s, errno=%d, details: %s\n", path, errno, strerror(errno));
				return -1;
		}

		std::cout << ".f_type: " << sfs.f_type << std::endl;
		std::cout << ".f_bsize: " << sfs.f_bsize << std::endl;
		std::cout << ".f_blocks: " << sfs.f_blocks << std::endl;
		std::cout << ".f_bfree: " << sfs.f_bfree << std::endl;
		std::cout << ".f_bavail: " << sfs.f_bavail << std::endl;
		std::cout << ".f_files: " << sfs.f_files << std::endl;
		std::cout << ".f_ffree: " << sfs.f_ffree << std::endl;

		std::string command = "df " + std::string(path);
    system(command.c_str());

    return 0;
}
