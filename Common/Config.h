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
	// 读取配置文件
	int parse_config(const std::string &path);
	
public :
	std::string _name;                    // 加速名称 
	std::string _srv_addr;                // Sloth系统的服务端地址
	unsigned short _srv_port;             // Sloth系统的服务端端口 
	unsigned short _local_port;           // 本地端口(本地代理的监听端口)
	std::string _remote_addr;             // 远端地址(远程需要加速的应用地址) 
	unsigned short _remote_port;          // 远端端口(远程需要加速的应用端口)
	int _up_bandwidth;        			  // 上行带宽
	int _down_bandwindth;      			  // 下行带宽 
};

#endif
