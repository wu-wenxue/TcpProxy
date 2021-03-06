#include "Client.h"

#include <thread>
#include "wxlogger_def.h"

using namespace wwx;
using namespace wxlog;

Client::Client(std::string server_ip, int port)
{
	m_server_ip = server_ip;
	m_port = port;
	Init();
}


Client::~Client()
{

}

bool Client::Init()
{
	//WSADATA wsaData;

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		std::cout << "Failed to load Winsock" << std::endl;
		return false;
	}

	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(m_port);
	addrSrv.sin_addr.S_un.S_addr = inet_addr(m_server_ip.c_str());

	sockClient = socket(AF_INET, SOCK_STREAM, 0);
	if (SOCKET_ERROR == sockClient)
	{
		std::cout << "Socket() error : " << WSAGetLastError() << std::endl;
		return false;
	}
	return true;
}

bool Client::Connect()
{
	if (connect(sockClient, (struct sockaddr*)&addrSrv, sizeof(addrSrv)) == INVALID_SOCKET)
	{
		std::cout << "Connect failed : " << WSAGetLastError() << std::endl;
		return false;
	}

//	std::thread t(onRecvMessage, this);
//	t.detach();
	return true;
}
/*
void Client::StartRecvProcess(WebSocket_Client* ws_client)
{
	std::thread t(onRecvMessage, ws_client);
	t.detach();
}
*/

bool Client::onSendMessage(char* message,int len)
{
	//std::string s_tmp;
	//int i_size = message.size();
	//for (int i = 0; i < i_size; i++)
	//{
	//	s_tmp += chToHex(message[i]);
	//}
	//WXLOG_DEBUG("client send : [ " << s_tmp << " ]");
	//std::cout << "send : " << message.c_str() << std::endl;
	int iSend = send(sockClient, message, len, 0);
	cout << "client send : " << iSend << endl;
	return true;

}

void Client::onRecvMessage(void* instance)
{
	std::cout << "recv thread is start ...." << std::endl;
	Client* client = static_cast<Client*>(instance);
	char recv_buf[1024];
	while (1)
	{
		std::string message = "";
		while (1)
		{
			memset(recv_buf, 0, sizeof(recv_buf));
			int len = recv(client->GetSocket(), recv_buf, sizeof(recv_buf)-1, 0);
			recv_buf[len] = '\0';
			message += recv_buf;
			if (len < sizeof(recv_buf))
			{
				if (len == 0)
				{
					std::cout << "connect is break....." << std::endl;
					break;
				}
				break;
			}
		}
		
		//std::cout << "socket recv : " << recv_buf << std::endl;
	}
}

int Client::Recv(std::string& recv_message)
{
	char recv_buf[1024] = { 0 };
	int count = 0;
	while (1)
	{
		memset(recv_buf, 0, sizeof(recv_buf));
		int len = recv(sockClient, recv_buf, sizeof(recv_buf)-1, 0);
		recv_buf[len] = '\0';
		count += len;
		recv_message += recv_buf;
		if (len < (sizeof(recv_buf)-1))
			break;
	}
	return count;
}

void Client::close()
{
	closesocket(sockClient);
	WSACleanup();
}

SOCKET Client::GetSocket()
{
	return sockClient;
}