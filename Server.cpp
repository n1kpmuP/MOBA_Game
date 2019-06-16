#include "winsock2.h"
#pragma comment(lib, "ws2_32.lib")
#include <iostream>
#include "..\wzry\wzry\Server.h"

using namespace std;

const int BUF_SIZE = 1024;
int bready = 0;

DWORD WINAPI GameServer ::ServerThread(LPVOID lp) {
	SOCKET *ClientSocket = (SOCKET*)lp;
	int receByt = 0;
	char RecvBuf[BUF_SIZE];
	while (true) {
		if (bready) {
			send(*ClientSocket, "start", sizeof("start"), 0);
			while (true) {
				ZeroMemory(RecvBuf, BUF_SIZE);
				receByt = recv(*ClientSocket, RecvBuf, sizeof(RecvBuf), 0);
				if (receByt > 0) {
					if (*ClientSocket == *ClientSocket1) {
						send(*ClientSocket2, RecvBuf, sizeof(RecvBuf), 0);
					}
					else if (*ClientSocket == *ClientSocket2) {
						send(*ClientSocket1, RecvBuf, sizeof(RecvBuf), 0);
					}
				}
			}
		}
	}
	closesocket(*ClientSocket);
	free(ClientSocket);
	return 0;
}

GameServer::GameServer()
{
	WSADATA            wsd;            //WSADATA变量
	int                retVal;            //返回值
	//初始化套结字动态库
	if (WSAStartup(MAKEWORD(2, 2), &wsd) != 0)
	{
		cout << "WSAStartup failed!" << endl;
		fflush(stdout);
		return ;
	}

	//创建套接字
	ServerSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (INVALID_SOCKET == ServerSocket)
	{
		cout << "socket failed!" << endl;
		fflush(stdout);
		WSACleanup();//释放套接字资源;
		return ;
	}

	//服务器套接字地址 
	addrServ.sin_family = AF_INET;
	addrServ.sin_port = htons(4999);
	addrServ.sin_addr.s_addr = INADDR_ANY;
	//绑定套接字
	retVal = bind(ServerSocket, (LPSOCKADDR)&addrServ, sizeof(SOCKADDR_IN));
	if (SOCKET_ERROR == retVal)
	{
		cout << "bind failed!" << endl;
		fflush(stdout);
		closesocket(ServerSocket);    //关闭套接字
		WSACleanup();            //释放套接字资源;
		return ;
	}

	//开始监听 
	retVal = listen(ServerSocket, 1);
	if (SOCKET_ERROR == retVal)
	{
		cout << "listen failed!" << endl;
		fflush(stdout);
		closesocket(ServerSocket);    //关闭套接字
		WSACleanup();            //释放套接字资源;
		return ;
	}

	//循环接收客户端连接请求并创建服务线程

	ClientSocket1 = (SOCKET*)malloc(sizeof(SOCKET));
	ClientSocket2 = (SOCKET*)malloc(sizeof(SOCKET));
	HANDLE hThread1;
	HANDLE hThread2;
	//接收客户端连接请求
	*ClientSocket1 = accept(ServerSocket, 0, 0);
	cout << "一号客户端已连接,socket是:" << *ClientSocket1 << endl;
	fflush(stdout);
	hThread1 = CreateThread(NULL, 0, &ServerThread, ClientSocket1, 0, NULL);
	*ClientSocket2 = accept(ServerSocket, 0, 0);
	cout << "二号客户端已连接,socket是:" << *ClientSocket2 << endl;
	fflush(stdout);
	hThread2 = CreateThread(NULL, 0, &ServerThread, ClientSocket2, 0, NULL);
	CloseHandle(hThread1);
	CloseHandle(hThread2);
	bready = 1;
	//退出
	return ;
}

GameServer::~GameServer()
{
	closesocket(ServerSocket);
	WSACleanup();
}