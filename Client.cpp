/*************************************************************************
      > File Name: Client.cpp
      > Author: Raiden  
      > Mail: jungzhang@xiyoulinux.org
      > Created Time: Thu Sep 28 00:52:47 2017
 ************************************************************************/

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

