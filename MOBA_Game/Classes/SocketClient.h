#pragma once

//客户端：

#ifndef __SOCKET_CLIENT_H__ 
#define __SOCKET_CLIENT_H__ 
#include "SocketBase.h" 

class SocketClient : public SocketBase 
{ 

public: 
	SocketClient(void); 
~SocketClient(void);
bool connectServer(const char* serverIP, unsigned short port);    //连接服务器
void sendMessage(const char* data, int count);         //向服务端发送信息

std::function<void(const char* data, int count)> onRecv;     //接受服务器数据的回调函数
std::function<void()> onDisconnect;          //断开连接的回调函数

private:
	bool initClient(); 
void recvMessage(); 

private: 
	HSocket _socketServer;
	HSocket _socektClient;

}; 
#endif
