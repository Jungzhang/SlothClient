/*************************************************************************
  2     > File Name: RUDPClient.h
  3     > Author: Raiden  
  4     > Mail: jungzhang@xiyoulinux.org
  5     > Created Time: Thu Sep 28 00:52:47 2017
  6  ************************************************************************/
  
#ifndef __RUDPCLIENT_H__
#define __RUDPCLIENT_H__

#ifdef WIN32
	#include <winsock2.h>
	#include <ws2tcpip.h>
#endif

#include <udt/udt.h>

class RUDPClient {

public : 
	
	/*
		析构函数, 因为里边用到了动态分配内存, 所以必须要有该析构函数 
	*/ 
	~RUDPClient();
	
	/*
		初始化相关信息
		@return：
			0 : 成功
		  非0 ：失败 
	*/
	int init(const std::string &addr, const unsigned short port);
	
	/*
		建立可靠UDP连接
		@return :
			0 : 成功
		  非0 : 失败 
	*/
	int connect();
	
	/*
		读取数据
		@para-1 : 缓存区
		@para-2 : 长度
		@return :
			-1  : 失败
			 0  : 对方关闭连接
		    >0  : 接收到的数据长度 
	*/
	int recv(char *buf, int len);
	
	/*
		发送数据
		@para-1 : 发送数据的缓存区
		@para-2 : 待发送数据长度
		@return : 
			-1  : 失败
			>0  : 成功发送数据的长度 
	*/
	int send(const char *buf, int len);

private : 
	struct addrinfo _srv_info;      // 服务端信息  
	UDTSOCKET _srv_handler;         // 建立的UDTSOCKET对象 
};

#endif
  
