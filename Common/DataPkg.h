/*************************************************************************
  2     > File Name: DataPkg.h
  3     > Author: Raiden  
  4     > Mail: jungzhang@xiyoulinux.org
  5     > Created Time: Thu Sep 28 00:52:47 2017
  6  ************************************************************************/

#ifndef __DATAPKG_H__
#define __DATAPKG_H__  

#include <vector>
#include <memory>

/*
	���ṹ��
		1�ֽڣ�TCP(1)/UDP(2)
		Other�����ݲ��� 
*/ 

class DataPkg {
public : 
	DataPkg(bool isTcp, char *data, int len) : 
		_isTcp(isTcp), _data(data, data+len) { }
#ifdef WIN32
	// VS2010��֧�ָ�����
	DataPkg() {}
#else
	DataPkg() = default;
#endif

	// ���л���
	std::shared_ptr<char> serialize();
	
	// �����л�
	int deserialize(const char *data, int len);
	
	// ��ð�����
	int size();	 

private : 
	bool _isTcp;   				// �ǲ���TCP���� 
	std::vector<char> _data;	// ����  
};

#endif