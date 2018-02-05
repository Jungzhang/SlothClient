/*************************************************************************
       > File Name: Config.h
       > Author: Raiden  
       > Mail: jungzhang@xiyoulinux.org
       > Created Time: Thu Sep 28 00:52:47 2017
 ************************************************************************/

#ifndef __CONFIG__H
#define __CONFIG__H

#include <iostream>

class Config {

public : 
	// ��ȡ�����ļ�
	int parse_config(const std::string &path);
	
public :
	std::string _name;                    // �������� 
	std::string _srv_addr;                // Slothϵͳ�ķ���˵�ַ
	unsigned short _srv_port;             // Slothϵͳ�ķ���˶˿� 
	unsigned short _local_port;           // ���ض˿�(���ش���ļ����˿�)
	std::string _remote_addr;             // Զ�˵�ַ(Զ����Ҫ���ٵ�Ӧ�õ�ַ) 
	unsigned short _remote_port;          // Զ�˶˿�(Զ����Ҫ���ٵ�Ӧ�ö˿�)
	int _up_bandwidth;        			  // ���д���
	int _down_bandwindth;      			  // ���д��� 
};

#endif
