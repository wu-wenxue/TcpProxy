#include "AppCore.h"
#include <thread>
#include "wxlogger_def.h"

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
	char recv_buf[10240] = { 0 };
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
	char recv_buf[10240] = { 0 };
	while (1)
	{
		memset(recv_buf, 0, sizeof(recv_buf));
		int len = recv(m_server->GetClientSocket(), recv_buf, sizeof(recv_buf), 0);

		int i_size = strlen(recv_buf);
		if (i_size == 0)
		{
			continue;
		}

		std::string s_tmp;
		for (int i = 0; i < i_size; i++)
		{
			s_tmp += chToHex(recv_buf[i]);
		}
		WXLOG_DEBUG("server recv : [ " << s_tmp << " ]");

		m_client->onSendMessage(recv_buf);
//		int isend = send(m_client->GetSocket(), recv_buf, sizeof(recv_buf), 0);
	}
}