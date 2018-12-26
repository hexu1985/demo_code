// Client.cpp : Defines the entry point for the console application.
//

#define	BUF_SZIE	64
#include "winsock2.h"
//#pragma comment(lib, "ws2_32.lib")
#include <cstdio>

int main(int argc, char* argv[])
{

	WSADATA			wsd;			//WSADATA变量
	SOCKET			sHost;			//服务器套接字
	SOCKADDR_IN		servAddr;		//服务器地址
	char			buf[BUF_SZIE];	//接收数据缓冲区
	int				retVal;			//返回值
	
	//初始化套结字动态库
	if (WSAStartup(MAKEWORD(2,2), &wsd) != 0)
	{
		printf("WSAStartup failed!\n");
		return -1;
	}
	
	//创建套接字
	sHost = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);	
	if(INVALID_SOCKET == sHost)
	{
		printf("socket failed!\n");
		WSACleanup();//释放套接字资源
		return  -1;
	}

	//设置服务器地址
	servAddr.sin_family =AF_INET;
	servAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	servAddr.sin_port = htons((short)4999);
	int	nServAddlen  = sizeof(servAddr);

	//连接服务器
	retVal=connect(sHost,(LPSOCKADDR)&servAddr, sizeof(servAddr));	
	if(SOCKET_ERROR == retVal)
	{
		printf("connect failed!\n");	
		closesocket(sHost);	//关闭套接字
		WSACleanup();		//释放套接字资源
		return -1;
	}
	
	//向服务器发送数据
	ZeroMemory(buf, BUF_SZIE);
	strcpy(buf, "MyTCP");
	retVal = send(sHost, buf, strlen(buf), 0);
	if (SOCKET_ERROR == retVal)
	{
		printf("send failed!\n");
		closesocket(sHost);	//关闭套接字
		WSACleanup();		//释放套接字资源
		return -1;
	}
	
	//退出
	closesocket(sHost);	//关闭套接字
	WSACleanup();		//释放套接字资源
	return 0;
}

