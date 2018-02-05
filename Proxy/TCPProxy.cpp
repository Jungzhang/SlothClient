/*************************************************************************
      > File Name: TCPProxy.cpp
      > Author: Raiden  
      > Mail: jungzhang@xiyoulinux.org
      > Created Time: Thu Sep 28 00:52:47 2017
 ************************************************************************/


#include <thread>

#ifdef WIN32
	#include <winsock2.h>
	#include <windows.h> 
#endif

#include <udt/udt.h>

#include "TCPProxy.h"
#include "../Common/DataPkg.h"
#include "../Common/InfoPkg.h"
#include "../RUDP/RudpClient.h"

#ifdef WIN32
	#pragma comment(lib,"ws2_32.lib")
#endif

void TCPProxy::start()
{
#ifdef WIN32
	//初始化WSA  
	_sockVersion = MAKEWORD(2, 2);
	if (WSAStartup(_sockVersion, &_wsaData) != 0)
	{
		return;
	}
#endif

	//创建套接字  
	_listen = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (_listen == INVALID_SOCKET)
	{
		// TODO: 改为日志输出
		printf("socket error !\n");
		return;
	}

	//绑定IP和端口  
	_addr.sin_family = AF_INET;
	_addr.sin_port = htons(_config._local_port);
	_addr.sin_addr.S_un.S_addr = INADDR_ANY;
	if (bind(_listen, (LPSOCKADDR)&_addr, sizeof(_addr)) == SOCKET_ERROR)
	{
		// TODO: 改为日志输出
		printf("bind error !\n");
		return;
	}

	// 转化为监听套接字  
	if (listen(_listen, 5) == SOCKET_ERROR)
	{
		// TODO: 改为日志输出
		printf("listen error !\n");
		return;
	}

	SOCK client;

    struct sockaddr_in peerAddr;  
	int addrLen = sizeof(peerAddr);
    
    while(1)
    {
		client = accept(_listen, (struct sockaddr *)&peerAddr, &addrLen);
        if(client == INVALID_SOCKET)  
        {  
			// TODO:改为日志输出
            printf("accept error !\n");
            continue;  
        }
		// TODO: del
		printf("new proxy client connected\n");
        // 开启一个线程执行相应操作
		std::thread t(std::bind(&TCPProxy::worker, this, client, peerAddr));
		t.detach();
	} 
}

void TCPProxy::worker(SOCK client, struct sockaddr_in clientAddr)
{
	// 构造远端应用服务器的信息包
	InfoPkg info(inet_addr(_config._remote_addr.c_str()), _config._remote_port);
	 
	// 建立可靠UDP连接
	RUDPClient rudp;
	rudp.init(_config._srv_addr, _config._srv_port);
	if (rudp.connect() < 0)
	{
		// TODO: 改成日志输出
		printf("connect server failed\n");
		return;
	}

	// 发送机器信息
	if (rudp.send(info.serialize().get(), info.size()) != info.size())
	{
		// TODO: 改成日志输出
		printf("send application info failed, %s\n", UDT::getlasterror().getErrorMessage());
		return;
	}

	int epid = UDT::epoll_create();
	if (epid == UDT::ERROR)
	{
		// TODO: 改为日志输出
		printf("epoll create failed, %s\n", UDT::getlasterror().getErrorMessage());
		return;
	}
	int events = UDT_EPOLL_IN;
	UDT::epoll_add_usock(epid, rudp._srv_handler, &events);
	UDT::epoll_add_ssock(epid, client, &events);

	bool flag = false;
	while (!flag)
	{
		char buf[10240];
		std::set<UDTSOCKET> udtfds;
		std::set<SYSSOCKET> sysfds;
		int ret = UDT::epoll_wait(epid, &udtfds, NULL, -1, &sysfds, NULL);

		if (ret == UDT::ERROR)
		{
			// TODO: 改为日志输出
			printf("epoll_wait failed, %s\n", UDT::getlasterror().getErrorMessage());
			continue;
		}

		// UDTSOCKET上来数据
		for (auto it : udtfds)
		{
			int len = UDT::recv(it, buf, 10240, 0);
			if (len > 0)
			{
				// 发送数据给TCPProxy的客户端
				::send(client, buf, len, 0);
			}
			else if (len == UDT::ERROR)
			{
				// TODO: 改为日志输出
				printf("udt recv failed, %s\n", UDT::getlasterror().getErrorMessage());
				flag = true;
				break;
			}
			else
			{
				// TODO: 改为日志输出
				printf("udt socket closed, %s\n", UDT::getlasterror().getErrorMessage());
				flag = true;
				break;
			}
		}

		// SYSSOCKET上来数据
		for (auto it : sysfds)
		{
			int len = ::recv(it, buf, 10240, 0);
			if (len > 0)
			{
				// 发送数据给TCPProxy的客户端
				int ret = UDT::send(rudp._srv_handler, buf, len, 0);
				if (ret == UDT::ERROR)
				{
					// TODO: 改为日志输出
					printf("ust send failed, %s\n", UDT::getlasterror().getErrorMessage());
					flag = true;
					break;
				}
			}
			else if (len == UDT::ERROR)
			{
				// TODO: 改为日志输出
				printf("recv failed\n");
				flag = true;
				break;
			}
			else
			{
				// TODO: 改为日志输出
				//printf("proxy client socket closed\n");
				flag = true;
				break;
			}
		}
	}

	// 资源回收
	// 关闭UDTSOCKET
	UDT::close(rudp._srv_handler);
	// 关闭TCPProxy的socket
	#ifdef WIN32
		::closesocket(client);
	#else
		::close(client);
	#endif
	// 从epoll中移除
	UDT::epoll_remove_ssock(epid, client);
	UDT::epoll_remove_usock(epid, rudp._srv_handler);
}

void TCPProxy::recvUDT(SOCK notice, RUDPClient rudp)
{
	int len;
	char buf[10240];

	while (true)
	{
		len = rudp.recv(buf, 10240);
		if (len <= 0)
		{
			// TODO: 改为日志输出
			printf("rudp recv failed\n");
			break;
		}
		
		// 发回给Proxy的客户端
		int ret = send(notice, buf, len, 0);
		if (ret <= 0)
		{
			break;
		}
	}

	closesocket(notice);
}

int TCPProxy::init(Config config)
{
	_config = config;
	
	return 0;
}
