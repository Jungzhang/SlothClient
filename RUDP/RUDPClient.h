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
		��������, ��Ϊ����õ��˶�̬�����ڴ�, ���Ա���Ҫ�и��������� 
	*/ 
	~RUDPClient();
	
	/*
		��ʼ�������Ϣ
		@return��
			0 : �ɹ�
		  ��0 ��ʧ�� 
	*/
	int init(const std::string &addr, const unsigned short port);
	
	/*
		�����ɿ�UDP����
		@return :
			0 : �ɹ�
		  ��0 : ʧ�� 
	*/
	int connect();
	
	/*
		��ȡ����
		@para-1 : ������
		@para-2 : ����
		@return :
			-1  : ʧ��
			 0  : �Է��ر�����
		    >0  : ���յ������ݳ��� 
	*/
	int recv(char *buf, int len);
	
	/*
		��������
		@para-1 : �������ݵĻ�����
		@para-2 : ���������ݳ���
		@return : 
			-1  : ʧ��
			>0  : �ɹ��������ݵĳ��� 
	*/
	int send(const char *buf, int len);

private : 
	struct addrinfo _srv_info;      // �������Ϣ  
	UDTSOCKET _srv_handler;         // ������UDTSOCKET���� 
};

#endif
  
