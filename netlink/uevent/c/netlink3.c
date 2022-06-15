#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include <sys/types.h>
#include <asm/types.h>
#include <unistd.h>
//该头文件需要放在netlink.h前面防止编译出现__kernel_sa_family未定义
#include <sys/socket.h>
#include <linux/netlink.h>

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
    for (;;) {
        memset(buf, 0, sizeof(buf));
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
        for(i=0;i<len;i++) {
            if(*(buf+i)=='\0')
                buf[i]='\n';
            else if(!isprint(*(buf+i)))
                buf[i] = '.';
        }
        printf("received %d bytes\n%s\n",len,buf);
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
