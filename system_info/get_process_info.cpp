#include <stdio.h>
#include <string.h>
#include <unistd.h>
 
int main()
{
	pid_t pid = getpid();
	char strProcessPath[1024] = {0};
	if(readlink("/proc/self/exe", strProcessPath,1024) <=0)
	{
			return -1;
	}
 
	char *strProcessName = strrchr(strProcessPath, '/');
 
	if(!strProcessName)
	{
			printf("当前进程ID：%d\n", pid);
			printf("当前进程名：\n");
			printf("当前进程路径：%s\n", strProcessPath);
	}
	else
	{
			printf("当前进程ID：%d\n", pid);
			printf("当前进程名：%s\n", ++strProcessName);
			printf("当前进程路径：%s\n", strProcessPath);
	}
 
	return 0;
}
