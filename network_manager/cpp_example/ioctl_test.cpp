#include <stdio.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

int main(int argc,char*argv[])
{
    int s;
    int err;

    s=socket(AF_INET,SOCK_DGRAM,0);
    if(s<0){
        perror("socket error");
        return 0;
    }

    //传入网络接口序号，获得网络接口的名称
    struct ifreq ifr;
    ifr.ifr_ifindex=2;//获得第2个网络接口的名称 
    if (argc > 1) {
      ifr.ifr_ifindex=atoi(argv[1]);
    }
    err=ioctl(s,SIOCGIFNAME,&ifr);
    if(err){
        perror("index error");
    }else{
        printf("the %dst interface is:%s\n",ifr.ifr_ifindex,ifr.ifr_name);
    }

    //传入网络接口名称，获得标志
//    memcpy(ifr.ifr_name,"eth0",5);
    err=ioctl(s,SIOCGIFFLAGS,&ifr);
    if(!err){
        printf("SIOCGIFFLAGS:%d\n",ifr.ifr_flags);
    }

    //获得MTU和MAC
    err=ioctl(s,SIOCGIFMTU,&ifr);
    if(!err){
        printf("SIOCGIFMTU:%d\n",ifr.ifr_mtu);
    }

    //获得MAC地址
    err=ioctl(s,SIOCGIFHWADDR,&ifr);
    if(!err){
        unsigned char* hw=(unsigned char *)ifr.ifr_hwaddr.sa_data;
        printf("SIOCGIFHWADDR:%02x:%02x:%02x:%02x:%02x:%02x\n",hw[0],hw[1],hw[2],hw[3],hw[4],hw[5]);
    }

    //获得网卡映射参数 命令字SIOCGIFMAP
    err=ioctl(s,SIOCGIFMAP,&ifr);
    if(!err){
        printf("SIOCGIFMAP,mem_start:%d,mem_end:%d,base_addr:%d,ifr_map:%d,dma:%d,port:%d\n",ifr.ifr_map.mem_start,ifr.ifr_map.mem_end,ifr.ifr_map.base_addr,ifr.ifr_map.irq,ifr.ifr_map.dma,ifr.ifr_map.port);
    }

    //获得网卡序号
    err=ioctl(s,SIOCGIFINDEX,&ifr);
    if(!err){
        printf("SIOCGIFINDEX:%d\n",ifr.ifr_ifindex);
    }

    //获取发送队列的长度
    err=ioctl(s,SIOCGIFTXQLEN,&ifr);
    if(!err){
        printf("SIOCGIFTXQLEN:%d\n",ifr.ifr_qlen);
    }

    //获取网络接口IP
    struct sockaddr_in *sin=(struct sockaddr_in*)&ifr.ifr_addr;//保存的是二进制IP
    char ip[16];//字符数组，存放字符串
    memset(ip,0,16);
    err=ioctl(s,SIOCGIFADDR,&ifr);
    if(!err){
        inet_ntop(AF_INET,&sin->sin_addr.s_addr,ip,16);//转换的字符串保存到ip数组中，第二个参数是要转换的二进制IP指针，第三个参数是转换完成存放IP的缓冲区，最后一个参数是缓冲区的长度
        printf("SIOCGIFADDR:%s\n",ip);
    }

    //查询目标IP地址
    err=ioctl(s,SIOCGIFDSTADDR,&ifr);
    if(!err){
        inet_ntop(AF_INET,&sin->sin_addr.s_addr,ip,16);
        printf("SIOCGIFDSTADDR:%s\n",ip);
    }

    //查询子网掩码
    err=ioctl(s,SIOCGIFNETMASK,&ifr);
    if(!err){
        inet_ntop(AF_INET,&sin->sin_addr.s_addr,ip,16);
        printf("SIOCGIFNETMASK:%s\n",ip);
    }

    //设置IP地址，设置网络接口
    inet_pton(AF_INET,"222.27.253.108",&sin->sin_addr.s_addr);//将字符串IP转换成二进制
    err=ioctl(s,SIOCSIFADDR,&ifr);//发送设置本机ip地址请求命令
    if(!err){
        printf("check IP-----"); 
        memset(&ifr,0,sizeof(ifr));
        memcpy(ifr.ifr_name,"eth0",5);
        ioctl(s,SIOCGIFADDR,&ifr);
        inet_ntop(AF_INET,&sin->sin_addr.s_addr,ip,16);
        printf("%s\n",ip);
    }

    //得到接口的广播地址
    memset(&ifr,0,sizeof(ifr));
    memcpy(ifr.ifr_name,"eth0",5);
    ioctl(s,SIOCGIFBRDADDR,&ifr);
    struct sockaddr_in *broadcast=(struct sockaddr_in*)&ifr.ifr_broadaddr;
    //转换成字符串
    inet_ntop(AF_INET,&broadcast->sin_addr.s_addr,ip,16);//inet_ntop将二进制IP转换成点分十进制的字符串
    printf("BROADCAST IP:%s\n",ip);
    close(s);
}
