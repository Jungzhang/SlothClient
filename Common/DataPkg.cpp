/*************************************************************************
      > File Name: RUDPPackage.cpp
      > Author: Raiden  
      > Mail: jungzhang@xiyoulinux.org
      > Created Time: Thu Sep 28 00:52:47 2017
  ************************************************************************/

#include <memory>
#include <cstring>

#include "DataPkg.h"

std::shared_ptr<char> DataPkg::serialize()
{
	int len = this->size();
	std::shared_ptr<char> buf(new char[len]);
	
	if (buf == nullptr)
	{
		return nullptr; 
	}
	
	memcpy(buf.get(), &this->_isTcp, 1);
	memcpy(buf.get() + 1, this->_data.data(), this->_data.size());
	
	return buf;
}

int DataPkg::deserialize(const char *data, int len)
{
	// 包不完整(包头大小都是1字节呢) 
	if (len < 1)
	{
		return -1;
	} 
	
	memcpy(&this->_isTcp, data , 1);
	this->_data = std::move(std::vector<char> {data + 1, data + len});
	
	return 0;
}

int DataPkg::size()
{
	return _data.size() + 1;
}

