#include "winsock2.h"
#pragma comment(lib, "ws2_32.lib")
#include <iostream>
#include <string>

class GameServer
{
public:
	GameClient();
	~GameClient();
	static DWORD WINAPI SendThread(void *data);
	static DWORD WINAPI RecvThread(void *data);

private:
	SOCKET *ClientSocket1 = new SOCKET;
	SOCKET *ClientSocket2 = new SOCKET;
	static SOCKET      ServerSocket;        //�������׽���
	SOCKADDR_IN        addrServ;;        //��������ַ
};
