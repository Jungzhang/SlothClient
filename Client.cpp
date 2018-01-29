/*************************************************************************
  2     > File Name: Client.cpp
  3     > Author: Raiden  
  4     > Mail: jungzhang@xiyoulinux.org
  5     > Created Time: Thu Sep 28 00:52:47 2017
  6  ************************************************************************/

#include <iostream>

#include "Proxy/ClientProxy.h"

#ifdef WIN32
	#include <Windows.h>
#endif

int main(int argc, char *argv[])
{

#ifdef WIN32
	SetConsoleTitle("Sloth系统正在为您加速。。。。");
#endif
	ClientProxy client;
	client.start();
	
	return 0;
}

