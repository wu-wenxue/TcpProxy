#include "AppCore.h"
#include <thread>

AppCore::AppCore()
{
}


AppCore::~AppCore()
{
}

void AppCore::RegisterClient(wwx::Client* client)
{
	m_client = client;
}

void AppCore::RegisterServer(wwx::Server* server)
{
	m_server = server;
}

void AppCore::start()
{
	m_server->Accept();
	m_client->Connect();
	std::thread t1(&AppCore::ClientToServer, this);
	std::thread t2(&AppCore::ServerToClient, this);
	t1.detach();
	t2.detach();
}

void AppCore::ClientToServer()
{
	char recv_buf[1024] = { 0 };
	while (1)
	{
		memset(recv_buf, 0, sizeof(recv_buf));
		int len = recv(m_client->GetSocket(), recv_buf, sizeof(recv_buf), 0);

		m_server->onSendMessage(recv_buf);
//		int isend = send(m_server->GetClientSocket(), recv_buf, sizeof(recv_buf), 0);
	}
}

void AppCore::ServerToClient()
{
	char recv_buf[1024] = { 0 };
	while (1)
	{
		memset(recv_buf, 0, sizeof(recv_buf));
		int len = recv(m_server->GetClientSocket(), recv_buf, sizeof(recv_buf), 0);

		m_client->onSendMessage(recv_buf);
//		int isend = send(m_client->GetSocket(), recv_buf, sizeof(recv_buf), 0);
	}
}