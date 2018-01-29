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
	//��ʼ��WSA  
    _sockVersion = MAKEWORD(2,2);   
    if(WSAStartup(_sockVersion, &_wsaData)!=0)  
    {  
        return -1;  
    }  
  
    //�����׽���  
    _listen = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);  
    if(_listen == INVALID_SOCKET)  
    {  
        printf("socket error !\n");  
        return -1;  
    }  
  
    //��IP�Ͷ˿�  
    _addr.sin_family = AF_INET;
    _addr.sin_port = htons(_port);  
    _addr.sin_addr.S_un.S_addr = INADDR_ANY;   
    if(bind(_listen, (LPSOCKADDR)&_addr, sizeof(_addr)) == SOCKET_ERROR)  
    {
        printf("bind error !\n");
        return -1;
    }  
  
    // ת��Ϊ�����׽���  
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
        // ����һ���߳�ִ����Ӧ���� VS2010��֧��std::thread 
		std::thread t(std::bind(&TCPProxy::worker, this, client, remoteAddr));
		t.detach();
	} 
}

void TCPProxy::worker(SOCKET client, struct sockaddr_in clientAddr)
{
	// ����Զ��Ӧ�÷���������Ϣ��
	InfoPkg info(inet_addr(_config._remote_addr.c_str()), _config._remote_port);
	 
	// �����ɿ�UDP����, ����Զ�̻�����Ϣ���ݰ� 
	 
	 
	int len;
	char buffer[1024];
	while(1)
	{
		// �������� 
		len = recv(client, buffer, 1024, 0);
		if (len > 0)
		{
			// ����Э���
			DataPkg  pkg(true, buffer, len);
			// ���͵������
			 
		}
		else
		{
			break;
		}
	}
	
	closesocket(client);
}

