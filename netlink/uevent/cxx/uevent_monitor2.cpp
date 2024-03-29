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
#include <chrono>
#include <tuple>
#include <set>
#include <unordered_map>

#define UNIX_DOMAIN_OUTPUT  "/tmp/uevent"

struct Uevent {
    std::string action;
    std::string devpath;
    std::string subsystem;
    std::string devname;
    std::string devtype;
    std::chrono::steady_clock::time_point timestamp;
};

void print(const Uevent& uevent)
{
    std::cout << "action: " << uevent.action << ", "
              << "devpath: " << uevent.devpath << ", "
              << "subsystem: " << uevent.subsystem << ", "
              << "devname: " << uevent.devname << ", "
              << "devtype: " << uevent.devtype << std::endl;
}

std::tuple<std::string, std::string> split_line(const std::string& line)
{
    size_t pos = line.find('=');
    if (pos == std::string::npos)
        return std::tuple<std::string, std::string>();
    else
        return std::make_tuple(line.substr(0, pos), line.substr(pos+1));
}

bool str2Uevent(const std::string& data, std::chrono::steady_clock::time_point timestamp, Uevent& uevent)
{
    std::string line;
    std::istringstream is;
    is.str(data);
    std::string key;
    std::string value;
    std::set<std::string> key_set;
    while (std::getline(is, line)) {
        std::tie(key, value) = split_line(line);
        if (key.empty()) {
            std::cout << "key is empty" << std::endl;
            continue;
        }
        if (key == "ACTION") {
            uevent.action = value;
            key_set.insert(key);
        } else if (key == "DEVPATH") {
            uevent.devpath = value;
            key_set.insert(key);
        } else if (key == "SUBSYSTEM") {
            uevent.subsystem = value;
            key_set.insert(key);
        } else if (key == "DEVNAME") {
            uevent.devname = value;
            key_set.insert(key);
        } else if (key == "DEVTYPE") {
            if (value != "partition") {
                std::cout << "only focus partition device type, this device type: " << value << std::endl;
                return false;
            }
            uevent.devtype = value;
            key_set.insert(key);
        } else {
            // do nothing
        }
    }

    if (key_set.size() != 5) {
        std::cout << "key_set is not complete, key_set.size: " << key_set.size() << std::endl;
        return false;
    }

    uevent.timestamp = timestamp;
    return true;
}

void notifyUevent(const Uevent& uevent)
{
    print(uevent);
}

void processUevent(const Uevent& uevent)
{
    static std::unordered_map<std::string, std::chrono::steady_clock::time_point> udev_addtime_map;
    std::string action = uevent.action;

    if (action == "add") {
        std::cout << "new add action" << std::endl;

        auto iter = udev_addtime_map.find(uevent.devpath);
        if (iter != udev_addtime_map.end()) {
            auto span_time = uevent.timestamp - iter->second;
            if (span_time < std::chrono::seconds(10)) {
                std::cout << "an duplicate add action event" << std::endl;
                return;
            }
        } 
        udev_addtime_map[uevent.devpath] = uevent.timestamp;
        notifyUevent(uevent);
    } else if (action == "remove") {
        std::cout << "new remove action" << std::endl;

        auto iter = udev_addtime_map.find(uevent.devpath);
        if (iter == udev_addtime_map.end()) {
            std::cout << "an duplicate remove action event" << std::endl;
            return;
        }
        udev_addtime_map.erase(uevent.devpath);
        notifyUevent(uevent);
    } else {
        std::cout << "other action: " << action << std::endl;
    }
}

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
    Uevent uevent;
    std::chrono::steady_clock::time_point now;
    for (;;) {
        memset(buf,0,4096);
        len=recv(sockfd,buf,4096,0);
        now = std::chrono::steady_clock::now();
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
        if (pos == std::string::npos) {
            std::cout << "not find ACTION" << std::endl;
            continue;
        }

        if (str2Uevent(data.substr(pos), now, uevent)) {
            processUevent(uevent);
        }

        //std::cout << "received " << len << " bytes" << std::endl;
        //std::cout << data.substr(pos) << std::endl;
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
