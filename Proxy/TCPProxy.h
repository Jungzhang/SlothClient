/*************************************************************************
  2     > File Name: TCPProxy.cpp
  3     > Author: Raiden  
  4     > Mail: jungzhang@xiyoulinux.org
  5     > Created Time: Thu Sep 28 00:52:47 2017
  6  ************************************************************************/

#ifndef __TCPPROXY__H
#define __TCPPROXY__H

#ifdef WIN32
	#include <winsock2.h>
#else
#endif

#include <udt/udt.h>

#include "../Common/Config.h"
#include "../Common/typedefs.h"
#include "../RUDP/RUDPClient.h"

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
		@para-1: 和Proxy客户端创建的SOCKET
		@para-2: Proxy客户端的地址信息
		TCPProxy的业务处理
	*/
	void worker(SOCK client, struct sockaddr_in clientAddr);

	/*
		负责接收Server回传的UDT数据包,并且返回给Proxy的客户端
		@para-1 : 
	*/
	void recvUDT(SOCK &notice, RUDPClient &rudp);

private : 
	int _port;                 // Proxy监听的端口
	SOCK _listen;            // Proxy的listen socket
	struct sockaddr_in _addr;  // addr
	// Windows 相关 
	WORD _sockVersion;  
	WSADATA _wsaData;

	// 配置文件中的内容
	Config _config;	
};

#endif

