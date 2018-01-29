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
	包结构：
		1字节：TCP(1)/UDP(2)
		Other：数据部分 
*/ 

class DataPkg {
public : 
	DataPkg(bool isTcp, char *data, int len) : 
		_isTcp(isTcp), _data(data, data+len) { }

	DataPkg() = default;

	// 序列化包
	std::shared_ptr<char> serialize();
	
	// 反序列化
	int deserialize(const char *data, int len);

	// 取得包体
	std::vector<char> getData() { return _data; }
	
	// 获得包长度
	int size();	 

private : 
	bool _isTcp;   				// 是不是TCP流量 
	std::vector<char> _data;	// 数据  
};

#endif