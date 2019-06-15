#pragma once
//服务端:


#ifndef __SOCKET_SERVER_H__ 
#define __SOCKET_SERVER_H__ 
#include "SocketBase.h" 

class SocketServer : public SocketBase 
{ 
public:
static SocketServer* create(); 
SocketServer();
~SocketServer(); 
bool startServer(); 
void sendMessage(HSocket socket, const char* data, int count);      //向指定客户端发送信息
void sendMessage(const char* data, int count);     //向所有客户端发送信息
std::function<void(const char* ip)> onStart;      //服务端开启后的回调函数
std::function<void(HSocket socket)> onNewConnection;       //有新联接时的回调函数
std::function<void(const char* data, int count)> onRecv;   //有新消息时的回调函数
std::function<void(HSocket socket)> onDisconnect;          //有客户端断开的回调函数

private: 
bool initServer(); 
void acceptClient(); 
void acceptFunc();
void newClientConnected(HSocket socket); 
void recvMessage(HSocket socket); 

private: 
HSocket _socketServer; 

private:
	std::list<HSocket> _clientSockets;
}; 
#endif

