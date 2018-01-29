/*************************************************************************
  2     > File Name: ClientProxy.cpp
  3     > Author: Raiden  
  4     > Mail: jungzhang@xiyoulinux.org
  5     > Created Time: Thu Sep 28 00:52:47 2017
  6  ************************************************************************/

#include "ClientProxy.h" 

void ClientProxy::start()
{
	// 读取配置文件
	std::string path = "./config.json";
	Config config;
	int ret = config.parse_config(path);

	if (ret < 0)
	{
		// TODO: 日志输出
		printf("code = %d   Config file parsing failed\n", ret);
		return;
	}

	_tcp.init(config);
	_tcp.start();
}

