#include "winsock2.h"
#pragma comment(lib, "ws2_32.lib")
#include <iostream>
#include <string>

class GameServer
{
public:
	GameServer();
	~GameServer();
	static DWORD WINAPI ServerThread(void *data);

private:
	SOCKET *ClientSocket1 = new SOCKET;
	SOCKET *ClientSocket2 = new SOCKET;
	SOCKET            ServerSocket;        //�������׽���
	SOCKADDR_IN        addrServ;;        //��������ַ
};