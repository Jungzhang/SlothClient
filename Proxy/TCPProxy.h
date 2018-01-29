/*************************************************************************
  2     > File Name: TCPProxy.cpp
  3     > Author: Raiden  
  4     > Mail: jungzhang@xiyoulinux.org
  5     > Created Time: Thu Sep 28 00:52:47 2017
  6  ************************************************************************/

#ifndef __TCPPROXY__H
#define __TCPPROXY__H

#include <winsock2.h>

#include "../Common/Config.h"

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
		TCPProxy��ҵ����
	*/
	void worker(SOCKET client, struct sockaddr_in clientAddr);

private : 
	int _port;                 // �˿�
	SOCKET _listen;            // listen socket
	struct sockaddr_in _addr;  // addr
	// Windows ��� 
	WORD _sockVersion;  
	WSADATA _wsaData;

	// �����ļ��е�����
	Config _config;	
};

#endif

