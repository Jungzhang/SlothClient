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
	//��ʼ��WSA  
    _sockVersion = MAKEWORD(2,2);   
    if(WSAStartup(_sockVersion, &_wsaData)!=0)  
    {  
        return -1;  
    }
#endif
  
    //�����׽���  
    _listen = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);  
    if(_listen == INVALID_SOCKET)  
    {  
		// TODO: ��Ϊ��־���
        printf("socket error !\n");  
        return -1;  
    }  
  
    //��IP�Ͷ˿�  
    _addr.sin_family = AF_INET;
    _addr.sin_port = htons(_port);  
    _addr.sin_addr.S_un.S_addr = INADDR_ANY;   
    if(bind(_listen, (LPSOCKADDR)&_addr, sizeof(_addr)) == SOCKET_ERROR)  
    {
		// TODO: ��Ϊ��־���
        printf("bind error !\n");
        return -1;
    }  
  
    // ת��Ϊ�����׽���  
    if(listen(_listen, 5) == SOCKET_ERROR)  
    {  
		// TODO: ��Ϊ��־���
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
			// TODO:��Ϊ��־���
            printf("accept error !\n");
            continue;  
        }
        // ����һ���߳�ִ����Ӧ����
		std::thread t(std::bind(&TCPProxy::worker, this, client, peerAddr));
		t.detach();
	} 
}

void TCPProxy::worker(SOCK client, struct sockaddr_in clientAddr)
{
	// ����Զ��Ӧ�÷���������Ϣ��
	InfoPkg info(inet_addr(_config._remote_addr.c_str()), _config._remote_port);
	 
	// �����ɿ�UDP����
	RUDPClient rudp;
	rudp.init(_config._srv_addr, _config._srv_port);
	if (rudp.connect() < 0)
	{
		// TODO: �ĳ���־���
		printf("connect server failed\n");
		return;
	}

	// ���ͻ�����Ϣ
	if (rudp.send(info.serialize().get(), info.size()) != info.size())
	{
		// TODO: �ĳ���־���
		printf("send application info failed\n");
		return;
	}

	// ���������߳�
	std::thread t(std::bind(&TCPProxy::recvUDT, this, client, rudp));
	t.detach();

	int len;
	char buffer[1024];
	while(true)
	{
		// Proxy�ͻ��˷��͹�����TCP��Ϣ
		// �������� 
		len = recv(client, buffer, 1024, 0);
		if (len > 0)
		{
			// ����Э���
			DataPkg  pkg(true, buffer, len);
			// ���͵������
			if (rudp.send(pkg.serialize().get(), pkg.size()) < 0)
			{
				// TODO: �ĳ���־���
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
		
		// ���
		DataPkg pkg;
		pkg.deserialize(buf, len);
		
		// ���ظ�Proxy�Ŀͻ���
		int ret = send(notice, pkg.getData().data(), pkg.getData().size(), 0);
		if (ret <= 0)
		{
			break;
		}
	}

	closesocket(notice);
}
