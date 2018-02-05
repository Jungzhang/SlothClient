/*************************************************************************
      > File Name: ClientProxy.h
      > Author: Raiden  
      > Mail: jungzhang@xiyoulinux.org
      > Created Time: Thu Sep 28 00:52:47 2017
 ************************************************************************/

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

