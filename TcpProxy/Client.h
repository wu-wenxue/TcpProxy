#pragma once
#include <iostream>
//#include <windows.h>
#include <WinSock2.h>

#pragma comment(lib, "ws2_32.lib") 

namespace wwx
{

	class Client
	{
	public:
		Client(std::string server_ip, int port);
		~Client();

		bool Init();

		bool Connect();

		void onSendMessage(std::string message);

		//	void StartRecvProcess(WebSocket_Client* ws_client);

		static void onRecvMessage(void* instance);

		int Recv(std::string& recv_message);
		void close();

		SOCKET GetSocket();

	private:

		std::string m_server_ip;
		int m_port;

		WSADATA wsaData;
		SOCKADDR_IN addrSrv;
		SOCKET sockClient;


	};

}