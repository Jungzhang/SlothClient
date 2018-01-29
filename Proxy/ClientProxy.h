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

// �ͻ��˴��� 
class ClientProxy {

public : 
	
	// ���캯��,����˿�
	ClientProxy() = default;
	
	// �������� 
	void start();

private : 
	TCPProxy _tcp;    // TCP���� 
};

#endif

