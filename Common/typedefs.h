/*************************************************************************
2     > File Name: typedefs.h
3     > Author: Raiden
4     > Mail: jungzhang@xiyoulinux.org
5     > Created Time: Thu Sep 28 00:52:47 2017
6  ************************************************************************/

/*
	Ϊ����ĳЩ���汣��Դ��Ŀ�ƽ̨��, ���ø��ļ�
*/

#ifndef __TYPEDEFS_H__
#define __TYPEDEFS_H__

// ���ͷ�ļ�����
#ifdef WIN32
	#include <WinSock2.h>
#else
	#include <unistd.h>
#endif

// ��ؿ�ƽ̨�����ض���
#ifdef WIN32
	typedef SOCKET SOCK;
#else
	typedef int SOCK;
#endif

#endif