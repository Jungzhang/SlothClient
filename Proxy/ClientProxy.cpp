/*************************************************************************
      > File Name: ClientProxy.cpp
      > Author: Raiden  
      > Mail: jungzhang@xiyoulinux.org
      > Created Time: Thu Sep 28 00:52:47 2017
 ************************************************************************/

#include "ClientProxy.h" 

void ClientProxy::start()
{
	// ��ȡ�����ļ�
	std::string path = "./config.json";
	Config config;
	int ret = config.parse_config(path);

	if (ret < 0)
	{
		// TODO: ��־���
		printf("code = %d   Config file parsing failed\n", ret);
		return;
	}

	_tcp.init(config);
	_tcp.start();
}

