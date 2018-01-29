/*************************************************************************
  2     > File Name: Config.cpp
  3     > Author: Raiden  
  4     > Mail: jungzhang@xiyoulinux.org
  5     > Created Time: Thu Sep 28 00:52:47 2017
  6  ************************************************************************/

#include <iostream>
#include <fstream>

#include <json/json.h>

#include "Config.h"

/* ��ȡ�����ļ�
   @para-1 : �����ļ�·��
   @para-2 : �������֮��õ��Ľ��
   @retun  :
        0  : �ɹ� 
       -1  : ���ļ�ʧ��
	   -2  : json�ļ����� 
*/

int Config::parse_config(const std::string &path)
{
	std::ifstream config(path.c_str());
	
	if (!config.is_open())
	{
		return -1; // ���ļ�ʧ�� 
	}
	
	Json::Reader reader;
	Json::Value root;
	
	// ���������ļ�
	if (reader.parse(config, root))
	{
		_name = root["name"].asString();
		_local_port = root["local_port"].asInt();
		_srv_addr = root["server_addr"].asString();
		_srv_port = root["server_port"].asInt();
		_remote_addr = root["remote_addr"].asString();
		_remote_port = root["remote_port"].asInt();
		_up_bandwidth = root["up_bandwidth"].asInt();
		_down_bandwindth = root["down_bandwindth"].asInt();
		
	}
	else
	{
		return -2;  // Json�ļ����� 
	}
	
	return 0; // �ɹ�
}

