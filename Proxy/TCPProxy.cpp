/*************************************************************************
  2     > File Name: TCPProxy.cpp
  3     > Author: Raiden  
  4     > Mail: jungzhang@xiyoulinux.org
  5     > Created Time: Thu Sep 28 00:52:47 2017
  6  ************************************************************************/


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

int TCPProxy::init()
{
#ifdef WIN32
	//初始化WSA  
    _sockVersion = MAKEWORD(2,2);   
    if(WSAStartup(_sockVersion, &_wsaData)!=0)  
    {  
        return -1;  
    }
#endif
  
    //创建套接字  
    _listen = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);  
    if(_listen == INVALID_SOCKET)  
    {  
		// TODO: 改为日志输出
        printf("socket error !\n");  
        return -1;  
    }  
  
    //绑定IP和端口  
    _addr.sin_family = AF_INET;
    _addr.sin_port = htons(_port);  
    _addr.sin_addr.S_un.S_addr = INADDR_ANY;   
    if(bind(_listen, (LPSOCKADDR)&_addr, sizeof(_addr)) == SOCKET_ERROR)  
    {
		// TODO: 改为日志输出
        printf("bind error !\n");
        return -1;
    }  
  
    // 转化为监听套接字  
    if(listen(_listen, 5) == SOCKET_ERROR)  
    {  
		// TODO: 改为日志输出
        printf("listen error !\n");  
        return -1;  
    }
	
	return 0;
}

void TCPProxy::start()
{
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
		printf("send application info failed\n");
		return;
	}

	// 创建发送线程
	std::thread t(std::bind(&TCPProxy::recvUDT, this, client, rudp));
	t.detach();

	int len;
	char buffer[1024];
	while(true)
	{
		// Proxy客户端发送过来的TCP消息
		// 接收数据 
		len = recv(client, buffer, 1024, 0);
		if (len > 0)
		{
			// 构造协议包
			DataPkg  pkg(true, buffer, len);
			// 发送到服务端
			if (rudp.send(pkg.serialize().get(), pkg.size()) < 0)
			{
				// TODO: 改成日志输出
				printf("send data failed\n");
			}
		}
		else
		{
			break;
		}
	}
	
	closesocket(client);
}

void TCPProxy::recvUDT(SOCK &notice, RUDPClient &rudp)
{
	int len;
	char buf[1024];

	while (true)
	{
		len = rudp.recv(buf, 1024);
		if (len <= 0)
		{
			break;
		}
		
		// 拆包
		DataPkg pkg;
		pkg.deserialize(buf, len);
		
		// 发回给Proxy的客户端
		int ret = send(notice, pkg.getData().data(), pkg.getData().size(), 0);
		if (ret <= 0)
		{
			break;
		}
	}

	closesocket(notice);
}
