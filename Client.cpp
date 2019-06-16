#include "winsock2.h"
#include <iostream>
#include <string>
#include "..\client\client\Client.h"
#pragma comment(lib, "ws2_32.lib")

using namespace std;
const int BUF_SIZE = 1024;
int bready = 0;

DWORD WINAPI GameClient::SendThread(LPVOID lp)
{
	char sendBuf[1024];
	while (true) {
		if (bready) {
			while (true)
			{
				cin >> sendBuf;
				send(ServerSocket, sendBuf, sizeof(sendBuf), 0);
			}
		}
	}
}

DWORD WINAPI GameClient::RecvThread(LPVOID lp)
{
	char RecvBuf[BUF_SIZE];
	int receByt = 0;
	int tick = 0;
	while (true)
	{
		ZeroMemory(RecvBuf, BUF_SIZE);
		receByt = recv(ServerSocket, RecvBuf, sizeof(RecvBuf), 0);

		if (receByt > 0){
			if (strcmp(RecvBuf, "start") == 0) {
				bready = 1;
				cout << "start" << endl;
				fflush(stdout);
			}
			else{
			cout << RecvBuf << endl;
			fflush(stdout);
			}
		}
	}
}

GameClient::GameClient()
{

	WSADATA wsd; //WSADATA����
	int retVal; //����ֵ
	//��ʼ���׽��ֶ�̬��
	if (WSAStartup(MAKEWORD(2, 2), &wsd) != 0)
	{
		cout << "WSAStartup failed!" << endl;
		fflush(stdout);
		return -1;
	}
	//�����׽���
	ServerSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (INVALID_SOCKET == ServerSocket)
	{
		cout << "socket failed!" << endl;
		fflush(stdout);
		WSACleanup();//�ͷ��׽�����Դ
		return  -1;
	}

	//���÷�������ַ�Ͷ˿�
	ClientAddr.sin_family = AF_INET;
	ClientAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	ClientAddr.sin_port = htons((short)4999);
	int nServAddlen = sizeof(ClientAddr);

	//���ӷ�����
	retVal = connect(ServerSocket, (LPSOCKADDR)&ClientAddr, sizeof(ClientAddr));
	if (SOCKET_ERROR == retVal)
	{
		cout << "connect failed!" << endl;
		fflush(stdout);
		closesocket(ServerSocket);
		WSACleanup();
		return -1;
	}
	//���ӳɹ�
	unsigned long ulThreadId;

	hThread1 = CreateThread(NULL, 0, &RecvThread, NULL, 0, &ulThreadId);
	hThread2 = CreateThread(NULL, 0, &SendThread, NULL, 0, &ulThreadId);

	CloseHandle(hThread1);
	CloseHandle(hThread2);
	return 0;
}
GameClient::~GameClient()
{
	closesocket(ServerSocket);
	WSACleanup();
}