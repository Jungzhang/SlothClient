/*************************************************************************
  2     > File Name: ClientProxy.h
  3     > Author: Raiden  
  4     > Mail: jungzhang@xiyoulinux.org
  5     > Created Time: Thu Sep 28 00:52:47 2017
  6  ************************************************************************/

#ifndef __CLIENTPROXY_H__
#define __CLIENTPROXY_H__

#ifdef WIN32
	#include <winsock2.h>
#endif

#include "TCPProxy.h"

// 客户端代理 
class ClientProxy {

public : 
	
	// 构造函数,传入端口
	ClientProxy() = default;
	
	// 启动代理 
	void start();

private : 
	TCPProxy _tcp;    // TCP代理 
};

#endif

