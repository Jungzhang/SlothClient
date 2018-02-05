/*************************************************************************
      > File Name: TCPProxy.cpp
      > Author: Raiden  
      > Mail: jungzhang@xiyoulinux.org
      > Created Time: Thu Sep 28 00:52:47 2017
 ************************************************************************/

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
	void start();
	int init(Config config);

private : 
	/*
		@para-1: 和Proxy客户端创建的SOCKET
		@para-2: Proxy客户端的地址信息
		TCPProxy的业务处理
	*/
	void worker(SOCK client, struct sockaddr_in clientAddr);

	/*
		负责接收Server回传的UDT数据包,并且返回给Proxy的客户端(已废弃)
		@para-1 : TCP端口的socket对象
		@para-2 : UDT端口的socket对象
	*/
	void recvUDT(SOCK notice, RUDPClient rudp);

private : 
	SOCK _listen;            // Proxy的listen socket
	struct sockaddr_in _addr;  // addr
	// Windows 相关 
	WORD _sockVersion;  
	WSADATA _wsaData;

	// 配置文件中的内容
	Config _config;	
};

#endif

