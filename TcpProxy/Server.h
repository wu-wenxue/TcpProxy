#pragma once
#include <WinSock2.h>  
#include <stdio.h>  
#include <stdlib.h>  
#include <string>

#pragma comment(lib, "ws2_32.lib")  
namespace wwx
{
	class Server
	{
	public:
		Server(int port);
		~Server();

		void Init();

		void Bind();

		void Listen();

		bool Accept();

		bool onSendMessage(char* message,int len);

		void close();

		SOCKET GetClientSocket();
	private:
		WSADATA wsaData;
		SOCKADDR_IN addrClient;
		SOCKADDR_IN addrSrv;
		SOCKET sockSrv;
		SOCKET sockConn;
		int m_port;
	};
}
