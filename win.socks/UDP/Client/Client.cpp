// Client.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#define  BUF_SZIE	 64
#include "winsock2.h"
// #pragma comment(lib, "ws2_32.lib")

int main(int argc, char* argv[])
{
	
	WSADATA        wsd;				//WSADATA变量
	SOCKET         s;				//套接字
	SOCKADDR_IN    servAddr;		//服务器地址
	char			buf[BUF_SZIE];	//发送数据缓冲区
	
	//初始化套结字动态库
	if (WSAStartup(MAKEWORD(2,2), &wsd) != 0)
	{
		printf("WSAStartup failed!\n");
		return 1;
	}

	//创建套接字
	s = socket(AF_INET, SOCK_DGRAM, 0);
	if (s == INVALID_SOCKET)
	{
		printf("socket() failed; %d\n", WSAGetLastError());
		WSACleanup();//释放套接字资源
		return 1;
	}
	
	//赋值“MyUDP”
	ZeroMemory(buf, BUF_SZIE);
	strcpy(buf, "MyUDP");
	
	//服务器地址
	servAddr.sin_family =AF_INET;
	servAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	servAddr.sin_port = htons((short)5000);
	int	nServAddlen  = sizeof(servAddr);

	//发送数据
	if(sendto(s, buf, BUF_SZIE, 0, (SOCKADDR*)&servAddr, nServAddlen) == SOCKET_ERROR)
	{
		printf("recvfrom() failed: %d\n", WSAGetLastError());
		closesocket(s);	//关闭套接字
		WSACleanup();	//释放套接字资源
		return 1;
	}
	
	closesocket(s);		//关闭套接字	  
	WSACleanup();		//释放套接字资源
	return 0;
}

