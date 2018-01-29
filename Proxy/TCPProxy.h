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
		��ʼ����ز��� 
		@return : 0 �ɹ�, �� 0 ʧ�� 
	*/
	int init();
	/*
		@para-1: ��Proxy�ͻ��˴�����SOCKET
		@para-2: Proxy�ͻ��˵ĵ�ַ��Ϣ
		TCPProxy��ҵ����
	*/
	void worker(SOCK client, struct sockaddr_in clientAddr);

	/*
		�������Server�ش���UDT���ݰ�,���ҷ��ظ�Proxy�Ŀͻ���
		@para-1 : 
	*/
	void recvUDT(SOCK &notice, RUDPClient &rudp);

private : 
	int _port;                 // Proxy�����Ķ˿�
	SOCK _listen;            // Proxy��listen socket
	struct sockaddr_in _addr;  // addr
	// Windows ��� 
	WORD _sockVersion;  
	WSADATA _wsaData;

	// �����ļ��е�����
	Config _config;	
};

#endif

