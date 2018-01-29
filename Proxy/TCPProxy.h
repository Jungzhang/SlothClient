/*************************************************************************
  2     > File Name: TCPProxy.cpp
  3     > Author: Raiden  
  4     > Mail: jungzhang@xiyoulinux.org
  5     > Created Time: Thu Sep 28 00:52:47 2017
  6  ************************************************************************/

#ifndef __TCPPROXY__H
#define __TCPPROXY__H

#include <winsock2.h>

#include "../Common/Config.h"

class TCPProxy {

public :
	TCPProxy(int port) : _port(port) { }
	void start();

private : 
	/*
		初始化相关操作 
		@return : 0 成功, 非 0 失败 
	*/
	int init();
	/*
		TCPProxy的业务处理
	*/
	void worker(SOCKET client, struct sockaddr_in clientAddr);

private : 
	int _port;                 // 端口
	SOCKET _listen;            // listen socket
	struct sockaddr_in _addr;  // addr
	// Windows 相关 
	WORD _sockVersion;  
	WSADATA _wsaData;

	// 配置文件中的内容
	Config _config;	
};

#endif

