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

/* 读取配置文件
   @para-1 : 配置文件路径
   @para-2 : 解析完成之后得到的结果
   @retun  :
        0  : 成功 
       -1  : 打开文件失败
	   -2  : json文件有误 
*/

int Config::parse_config(const std::string &path)
{
	std::ifstream config(path.c_str());
	
	if (!config.is_open())
	{
		return -1; // 打开文件失败 
	}
	
	Json::Reader reader;
	Json::Value root;
	
	// 解析配置文件
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
		return -2;  // Json文件错误 
	}
	
	return 0; // 成功
}

