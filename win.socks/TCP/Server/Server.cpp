// Server.cpp : Defines the entry point for the console application.
//

#define  BUF_SZIE	 64
#include "winsock2.h"
//#pragma comment(lib, "ws2_32.lib")
#include <cstdio>

int main(int argc, char* argv[])
{
	WSADATA			wsd;			//WSADATA变量
	SOCKET			sServer;		//服务器套接字
	SOCKET			sClient;		//客户端套接字
	SOCKADDR_IN		addrServ;;		//服务器地址
	char			buf[BUF_SZIE];	//接收数据缓冲区
	int				retVal;			//返回值

	//初始化套结字动态库
	if (WSAStartup(MAKEWORD(2,2), &wsd) != 0)
	{
		printf("WSAStartup failed!\n");
		return 1;
	}
	
	//创建套接字
	sServer = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);	
	if(INVALID_SOCKET == sServer)
	{
		printf("socket failed!\n");
		WSACleanup();//释放套接字资源;
		return  -1;
	}
	
	//服务器套接字地址 
	addrServ.sin_family = AF_INET;
	addrServ.sin_port = htons(4999);
	addrServ.sin_addr.s_addr = INADDR_ANY;		
	//绑定套接字
	retVal = bind(sServer, (LPSOCKADDR)&addrServ, sizeof(SOCKADDR_IN));
	if(SOCKET_ERROR == retVal)
	{	
		printf("bind failed!\n");
		closesocket(sServer);	//关闭套接字
		WSACleanup();			//释放套接字资源;
		return -1;
	}
	
	//开始监听 
	retVal = listen(sServer, 1);
	if(SOCKET_ERROR == retVal)
	{
		printf("listen failed!\n");		
		closesocket(sServer);	//关闭套接字
		WSACleanup();			//释放套接字资源;
		return -1;
	}
	
	//接受客户端请求
	sockaddr_in addrClient;
	int addrClientlen = sizeof(addrClient);
	sClient = accept(sServer,(sockaddr FAR*)&addrClient, &addrClientlen);
	if(INVALID_SOCKET == sClient)
	{
		printf("accept failed!\n");		
		closesocket(sServer);	//关闭套接字
		WSACleanup();			//释放套接字资源;
		return -1;
	}
	
	//接收客户端数据
	ZeroMemory(buf, BUF_SZIE);
	retVal = recv(sClient, buf, BUF_SZIE, 0);
	if (SOCKET_ERROR == retVal)
	{
		printf("recv failed!\n");		
		closesocket(sServer);	//关闭套接字
		closesocket(sClient);	//关闭套接字		
		WSACleanup();			//释放套接字资源;
		return -1;
	}

	printf("%s\n", buf);	//输出"MyTCP"	

	//退出
	closesocket(sServer);	//关闭套接字
	closesocket(sClient);	//关闭套接字
	WSACleanup();			//释放套接字资源;
	return 0;
}

