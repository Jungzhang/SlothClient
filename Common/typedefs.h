/*************************************************************************
2     > File Name: typedefs.h
3     > Author: Raiden
4     > Mail: jungzhang@xiyoulinux.org
5     > Created Time: Thu Sep 28 00:52:47 2017
6  ************************************************************************/

/*
	为了在某些方面保持源码的跨平台性, 设置该文件
*/

#ifndef __TYPEDEFS_H__
#define __TYPEDEFS_H__

// 相关头文件包含
#ifdef WIN32
	#include <WinSock2.h>
#else
	#include <unistd.h>
#endif

// 相关跨平台类型重定义
#ifdef WIN32
	typedef SOCKET SOCK;
#else
	typedef int SOCK;
#endif

#endif