// Server.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#define  BUF_SZIE	 64
#include "winsock2.h"
//#pragma comment(lib, "ws2_32.lib")

int main(int argc, char* argv[])
{
	
	WSADATA			wsd;			//WSADATA变量
	SOCKET			s;				//套接字
	SOCKADDR_IN		servAddr;		//服务器地址
	char			buf[BUF_SZIE];	//接收数据缓冲区
	
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
	
	int nErrCode;	//返回值
	int nBufLen;	//接收数据缓冲区大小
	int nOptlen = sizeof(nBufLen);
	//获取接收数据缓冲区大小
	nErrCode = getsockopt(s, SOL_SOCKET, SO_RCVBUF,(char*)&nBufLen, &nOptlen);
	if (SOCKET_ERROR == nErrCode)
	{
		//处理失败
	}

	//设置接收数据缓冲区为原来的10倍
	nBufLen *= 10;
	nErrCode = setsockopt(s, SOL_SOCKET, SO_RCVBUF,(char*)&nBufLen, nOptlen);
	if (SOCKET_ERROR == nErrCode)
	{
		//失败处理
	}

	//检查设置系统接收数据缓冲区是否成功
	int uiNewRcvBuf;
	getsockopt(s, SOL_SOCKET, SO_RCVBUF,(char*)&uiNewRcvBuf, &nOptlen);
	if (SOCKET_ERROR == nErrCode || uiNewRcvBuf != nBufLen)
	{
		//失败处理
	}


	//服务器地址
	servAddr.sin_family = AF_INET;
	servAddr.sin_port = htons((short)5000);			//端口
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);	//IP
	
	//绑定
	if (bind(s, (SOCKADDR *)&servAddr, sizeof(servAddr)) == SOCKET_ERROR)
	{
		printf("bind() failed: %d\n", WSAGetLastError());
		closesocket(s);	//关闭套接字
		WSACleanup();	//释放套接字资源
		return 1;
	}	
	
	//接收数据
	SOCKADDR_IN clientAddr;
	int nClientLen = sizeof(clientAddr);
	ZeroMemory(buf, BUF_SZIE);
	if(recvfrom(s, buf, BUF_SZIE, 0, (SOCKADDR*)&clientAddr, &nClientLen) == SOCKET_ERROR)
	{
		printf("recvfrom() failed: %d\n", WSAGetLastError());
		closesocket(s);	//关闭套接字
		WSACleanup();	//释放套接字资源
		return 1;
	}	

	printf("%s\n", buf);//输出"MyUDP"
	
	closesocket(s);		//关闭套接字
	WSACleanup();		//释放套接字资源
	return 0;
}

	//设置系统接收数据为默认的BUF_TIMES倍
// 	unsigned int uiRcvBuf;
// 	int uiRcvBufLen = sizeof(uiRcvBuf);
// 	nErrCode= getsockopt(m_sHost, SOL_SOCKET, SO_RCVBUF,(char*)&uiRcvBuf, &uiRcvBufLen);
// 	if (SOCKET_ERROR == nErrCode)
// 	{
// 		return;
// 	}
// 	uiRcvBuf *= BUF_TIMES;
// 	nErrCode = setsockopt(m_sHost, SOL_SOCKET, SO_RCVBUF,(char*)&uiRcvBuf, uiRcvBufLen);
// 	if (SOCKET_ERROR == nErrCode)
// 	{
// 		AfxMessageBox(_T("修改系统发送数据缓冲区失败！"));
// 	}
// 
// 	//检查设置系统接收数据缓冲区是否成功
// 	unsigned int uiNewRcvBuf;
// 	getsockopt(m_sHost, SOL_SOCKET, SO_RCVBUF,(char*)&uiNewRcvBuf, &uiRcvBufLen);
// 	if (SOCKET_ERROR == nErrCode || uiNewRcvBuf != uiRcvBuf)
// 	{
// 		AfxMessageBox(_T("修改系统发送数据缓冲区失败！"));;
//	}
