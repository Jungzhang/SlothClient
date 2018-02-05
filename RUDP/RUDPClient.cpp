/*************************************************************************
      > File Name: RUDPClient.cpp
      > Author: Raiden  
      > Mail: jungzhang@xiyoulinux.org
      > Created Time: Thu Sep 28 00:52:47 2017
 ************************************************************************/
 
#include <iostream>
 
#include "RUDPClient.h"

RUDPClient::~RUDPClient()
{
	if (_srv_info.ai_addr)
	{
		free(_srv_info.ai_addr);
		_srv_info.ai_addr = nullptr;
	}
	UDT::close(_srv_handler);
	UDT::cleanup();
}

int RUDPClient::init(const std::string &addr, const unsigned short port)
{
	
	UDT::startup();
	struct addrinfo *peer;
	
	memset(&_srv_info, 0, sizeof(struct addrinfo));
	
	_srv_info.ai_family = AF_INET;
	_srv_info.ai_flags = AI_PASSIVE;
	_srv_info.ai_socktype = SOCK_STREAM;
	
	_srv_handler = UDT::socket(_srv_info.ai_family, _srv_info.ai_socktype, _srv_info.ai_protocol);
	
	if (0 != getaddrinfo(addr.c_str(), std::to_string((unsigned long long)port).c_str(), &_srv_info, &peer))
	{
		//TODO: 改成日志输出 
		std::cerr << "getaddrinfo error " << addr << ":" << port << std::endl;
		return -1;
	}
	
	_srv_info.ai_addr = (struct sockaddr *)malloc(sizeof(struct sockaddr));
	
	if (_srv_info.ai_addr == nullptr)
	{
		return -1;
	}
	
	memcpy(_srv_info.ai_addr, peer->ai_addr, sizeof(struct sockaddr));
	_srv_info.ai_addrlen = peer->ai_addrlen; 
	
	freeaddrinfo(peer);
	
	return 0;
}

int RUDPClient::connect()
{
	if (UDT::ERROR == UDT::connect(_srv_handler, _srv_info.ai_addr, _srv_info.ai_addrlen))
	{
		// TODO: 改为日志输出 
		std::cerr << "connect failed : " << UDT::getlasterror().getErrorMessage() << std::endl;
		return -1;
	}
	return 0;
}

int RUDPClient::recv(char *buf, int len)
{
	int ret = UDT::recv(_srv_handler, buf, len, 0);
	if (UDT::ERROR == ret)
	{
		// TODO: 改为日志输出
		std::cerr << "recv failed : " << UDT::getlasterror().getErrorMessage() << std::endl;
		return -1; 
	}
	
	return ret;
}

int RUDPClient::send(const char *buf, int len)
{
	int ret =  UDT::send(_srv_handler, buf, len, 0);
	if (UDT::ERROR == ret)
	{
		// TODO: 改为日志输出
		std::cerr << "send failed : " << UDT::getlasterror().getErrorMessage() << std::endl;
		return -1; 
	}
	
	return ret;
}
