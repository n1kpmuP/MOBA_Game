#pragma once
#ifndef __SOCKET_BASE_H__ 
#define __SOCKET_BASE_H__ 
#include "cocos2d.h" 
#include <list> 
#include <thread> 
USING_NS_CC; 
// 对于windows平台 
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) 
#include <WinSock2.h> 
#pragma comment(lib, "WS2_32.lib") 
#define HSocket SOCKET 
#define HSocket int 
#endif 
class SocketBase : public Ref 
{ 
public:
	SocketBase(); 
~SocketBase(); 

protected: 
	void closeConnect(HSocket socket); 
bool error(HSocket socket);

protected: 
	std::mutex _mutex; 

private: 
	bool _bInitSuccess;
}; 
#endif
