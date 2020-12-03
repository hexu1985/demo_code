#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <net/if.h>

#include <netinet/in.h>
#include <linux/netlink.h>
#include <linux/rtnetlink.h>
//#include <net/if.h>
#include <arpa/inet.h>

#include <signal.h>
#include <unistd.h>

FILE* fp=NULL;
int running = 1;

void nl_log(const char* fmt, ...)
{
  va_list ap;

  va_start(ap, fmt);
  if(fp != NULL){
    if (vfprintf(fp, fmt, ap) < 0){
      perror("fprintf");
    }
    fflush(fp);
  }
  vprintf(fmt, ap);
  va_end(ap);
}

void parseBinaryNetlinkMessage(struct nlmsghdr *nh) {
  int len = nh->nlmsg_len - sizeof(*nh);
  struct ifinfomsg *ifi;

  if (sizeof(*ifi) > (size_t) len) {
    nl_log("Got a short RTM_NEWLINK message\n");
    return;
  }

  ifi = (struct ifinfomsg *)NLMSG_DATA(nh);
  if ((ifi->ifi_flags & IFF_LOOPBACK) != 0) {
    return;
  }

  struct rtattr *rta = (struct rtattr *)
    ((char *) ifi + NLMSG_ALIGN(sizeof(*ifi)));
  len = NLMSG_PAYLOAD(nh, sizeof(*ifi));

  while(RTA_OK(rta, len)) {
    switch(rta->rta_type) {
      case IFLA_IFNAME:
        {
          char ifname[IFNAMSIZ];
          const char *action;
          snprintf(ifname, sizeof(ifname), "%s",
              (char *) RTA_DATA(rta));
          //action = (ifi->ifi_flags & IFF_LOWER_UP) ? "up" : "down";
          action = (ifi->ifi_flags & IFF_RUNNING) ? "up" : "down";
          nl_log("%s link %s\n", ifname, action);
        }
    }

    rta = RTA_NEXT(rta, len);
  }
}

void parseNetlinkAddrMsg(struct nlmsghdr *nlh, int is_new_addr)
{
  struct ifaddrmsg *ifa = (struct ifaddrmsg *) NLMSG_DATA(nlh);
  struct rtattr *rth = IFA_RTA(ifa);
  int rtl = IFA_PAYLOAD(nlh);

  while (rtl && RTA_OK(rth, rtl)) {
    if (rth->rta_type == IFA_LOCAL) {
      uint32_t ipaddr = htonl(*((uint32_t *)RTA_DATA(rth)));
      char name[IFNAMSIZ];
      if_indextoname(ifa->ifa_index, name);
      nl_log("%s %s address %d.%d.%d.%d\n",
          name, (is_new_addr != 0)?"add":"del",
          (ipaddr >> 24) & 0xff,
          (ipaddr >> 16) & 0xff,
          (ipaddr >> 8) & 0xff,
          ipaddr & 0xff);
    }
    rth = RTA_NEXT(rth, rtl);
  }
}

void signal_handle(int signo)
{
  nl_log("got signal:%d\n", signo);
  if(fp != NULL){
    fclose(fp);
  }
  exit(0);
}

int main(int argc, char* argv[])
{
  struct sockaddr_nl addr;
  int sock, len;
  char buffer[4096];
  struct nlmsghdr *nlh;
  const char* fname = "netlink.log";

  if (argc > 1 && strcmp(argv[1],"-f")==0){
    fp = fopen(fname, "w");
    if (fp == NULL){
      perror("fopen");
      return 1;
    }
    printf("netlink message will also write to %s. \n", fname);
  }

  signal(SIGINT, signal_handle);
  if ((sock = socket(PF_NETLINK, SOCK_RAW, NETLINK_ROUTE)) == -1) {
    perror("couldn't open NETLINK_ROUTE socket");
    return 1;
  }

  memset(&addr, 0, sizeof(addr));
  addr.nl_family = AF_NETLINK;
  addr.nl_groups = RTMGRP_LINK | RTMGRP_IPV4_IFADDR;

  if (bind(sock, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
    perror("couldn't bind");
    return 1;
  }

  while (running && (len = recv(sock, buffer, 4096, 0)) > 0) {
    nlh = (struct nlmsghdr *)buffer;
    while ((NLMSG_OK(nlh, len)) && (nlh->nlmsg_type != NLMSG_DONE)) {
      if (nlh->nlmsg_type == RTM_NEWADDR) {
        parseNetlinkAddrMsg(nlh, 1);
      }else if(nlh->nlmsg_type == RTM_DELADDR){
        parseNetlinkAddrMsg(nlh, 0);
      }else if (nlh->nlmsg_type == RTM_NEWLINK){
        parseBinaryNetlinkMessage(nlh);
      }
      nlh = NLMSG_NEXT(nlh, len);
    }
  }
  close(sock);
  if(fp != NULL){
    fclose(fp);
  }
  return 0;
}
