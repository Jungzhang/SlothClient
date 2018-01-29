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

#ifdef WIN32
	#pragma comment(lib,"ws2_32.lib")
#endif

int TCPProxy::init()
{
	//初始化WSA  
    _sockVersion = MAKEWORD(2,2);   
    if(WSAStartup(_sockVersion, &_wsaData)!=0)  
    {  
        return -1;  
    }  
  
    //创建套接字  
    _listen = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);  
    if(_listen == INVALID_SOCKET)  
    {  
        printf("socket error !\n");  
        return -1;  
    }  
  
    //绑定IP和端口  
    _addr.sin_family = AF_INET;
    _addr.sin_port = htons(_port);  
    _addr.sin_addr.S_un.S_addr = INADDR_ANY;   
    if(bind(_listen, (LPSOCKADDR)&_addr, sizeof(_addr)) == SOCKET_ERROR)  
    {
        printf("bind error !\n");
        return -1;
    }  
  
    // 转化为监听套接字  
    if(listen(_listen, 5) == SOCKET_ERROR)  
    {  
        printf("listen error !\n");  
        return -1;  
    }
	
	return 0;
}

void TCPProxy::start()
{
	SOCKET client;  
    struct sockaddr_in remoteAddr;  
    int addrLen = sizeof(remoteAddr);
    
    while(1)
    {
    	client = accept(_listen, (SOCKADDR *)&remoteAddr, &addrLen);  
        if(client == INVALID_SOCKET)  
        {  
            printf("accept error !\n");
            continue;  
        }
        // 开启一个线程执行相应操作 VS2010不支持std::thread 
		std::thread t(std::bind(&TCPProxy::worker, this, client, remoteAddr));
		t.detach();
	} 
}

void TCPProxy::worker(SOCKET client, struct sockaddr_in clientAddr)
{
	// 构造远端应用服务器的信息包
	InfoPkg info(inet_addr(_config._remote_addr.c_str()), _config._remote_port);
	 
	// 建立可靠UDP连接, 发送远程机器信息数据包 
	 
	 
	int len;
	char buffer[1024];
	while(1)
	{
		// 接收数据 
		len = recv(client, buffer, 1024, 0);
		if (len > 0)
		{
			// 构造协议包
			DataPkg  pkg(true, buffer, len);
			// 发送到服务端
			 
		}
		else
		{
			break;
		}
	}
	
	closesocket(client);
}

