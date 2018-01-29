/*************************************************************************
  2     > File Name: InfoPkg.h
  3     > Author: Raiden  
  4     > Mail: jungzhang@xiyoulinux.org
  5     > Created Time: Thu Sep 28 00:52:47 2017
  6  ************************************************************************/

#ifndef __INFOPKG_H__
#define __INFOPKG_H__

#include <memory>

/*
	���ṹ��
		4�ֽڣ�Զ��Ӧ�÷�����IP 
		2�ֽڣ�Զ��Ӧ�÷������˿� 
*/

class InfoPkg {

public :

#ifndef WIN32
	InfoPkg() = default;
#else
	InfoPkg() {}
#endif

	InfoPkg(int remoteAddr, unsigned int port) : _remoteAddr(remoteAddr), _port(port) { }
	
	// ���л�
	std::shared_ptr<char> serialize();
	
	// �����л�
	int deserialize(const char *data, int len);
	
	// ����
	int size(); 
	
private :
	int _remoteAddr;           // Զ��Ӧ�÷�����IP 
	unsigned short _port;       // Զ��Ӧ�÷������˿� 
};


#endif
  
