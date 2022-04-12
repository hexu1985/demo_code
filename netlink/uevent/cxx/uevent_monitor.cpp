#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <asm/types.h>
#include <unistd.h>
//该头文件需要放在netlink.h前面防止编译出现__kernel_sa_family未定义
#include <sys/socket.h>
#include <linux/netlink.h>
#include <iostream>
#include <string>
#include <sstream>
//#include <linux/rtnetlink.h>

void MonitorNetlinkUevent()
{
    int sockfd;
    struct sockaddr_nl sa;
    int len;
    char buf[4096];
    int i;

    memset(&sa,0,sizeof(sa));
    sa.nl_family=AF_NETLINK;
    sa.nl_groups=NETLINK_KOBJECT_UEVENT;
    sa.nl_pid = 0;//getpid(); both is ok

    sockfd=socket(AF_NETLINK,SOCK_RAW,NETLINK_KOBJECT_UEVENT);
    if(sockfd==-1)
        printf("socket creating failed:%s\n",strerror(errno));
    if(bind(sockfd,(struct sockaddr *)&sa,sizeof(sa))==-1)
        printf("bind error:%s\n",strerror(errno));

    int count = 0;
    std::string data;
    std::string line;
    std::istringstream is;
    for (;;) {
        memset(buf,0,4096);
        len=recv(sockfd,buf,4096,0);
        if(len<0) {
            printf("receive error\n");
            continue;
        } else if(len<32||len>sizeof(buf)) {
            printf("invalid message");
            continue;
        }

        count++;
        printf("***********************msg %d start***********************\n", count);
        for(i=0;i<len;i++)
            if(buf[i]=='\0')
                buf[i]='\n';

        data.clear();
        data.assign(buf, len);

        size_t pos = data.find("ACTION");
        if (pos != std::string::npos) {
            std::cout << "find ACTION" << std::endl;
        } else {
            std::cout << "not find ACTION" << std::endl;
            continue;
        }

        is.clear();
        is.str(data.substr(pos));
        while (std::getline(is, line)) {
            std::cout << "line: " << line << std::endl;
        }
        std::cout << "received " << len << " bytes" << std::endl;
        std::cout << data.substr(pos) << std::endl;
        printf("***********************msg %d ends************************\n", count);
        fflush(stdout);
    }
    close(sockfd);
}

int main(int argc,char **argv)
{
    printf("***********************start***********************\n");
    MonitorNetlinkUevent();
    printf("***********************ends************************\n");
    return 0;
}
