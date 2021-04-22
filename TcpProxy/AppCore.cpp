#include "AppCore.h"
#include <thread>
#include "wxlogger_def.h"

using namespace wxlog;
using namespace std;

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
	while (1)
	{

		if (m_server->Accept())
		{
			cout << "client connected, read to connect to server !" << endl;
			m_client->Connect();
		}
		std::thread t1(&AppCore::ClientToServer, this,this);

		std::thread t2(&AppCore::ServerToClient, this,this);
		
		t1.join();
		t2.join();

		cout << "link is disconnected ....." << endl;
	}
}

void AppCore::ClientToServer(void* obj)
{
	char recv_buf[10240] = { 0 };
	runFlag_c2s = true;
	while (1)
	{
		memset(recv_buf, 0, sizeof(recv_buf));
		int len = recv(m_client->GetSocket(), recv_buf, sizeof(recv_buf), 0);
		if (len <= 0)
		{
			WXLOG_ERROR("c2s disconnected !");
			cout << "sc2s disconnected !" << endl;
			break;
		}
		cout << "c2s recv : " << len << endl;

		std::string s_tmp;
		for (int i = 0; i < len; i++)
		{
			s_tmp += chToHex(recv_buf[i]);
		}

		cout << "c2s recv : " << len << " << " << s_tmp << endl;
		WXLOG_DEBUG("server recv : [ " << s_tmp << " ]");

		m_server->onSendMessage(recv_buf,len);
//		int isend = send(m_server->GetClientSocket(), recv_buf, sizeof(recv_buf), 0);
	}

	AppCore* instance = static_cast<AppCore*>(obj);
	instance->stopThreadS2C();
}

void AppCore::ServerToClient(void* obj)
{
	char recv_buf[10240] = { 0 };

	runFlag_s2c = true;
	while (1)
	{
		memset(recv_buf, 0, sizeof(recv_buf));
		int len = recv(m_server->GetClientSocket(), recv_buf, sizeof(recv_buf), 0);
		if (len <= 0)
		{
			WXLOG_ERROR("s2c disconnected !");
			cout << "s2c disconnected !" << endl;
			break;
		}
		cout << "s2c recv : " << len << endl; 

		std::string s_tmp;
		for (int i = 0; i < len; i++)
		{
			s_tmp += chToHex(recv_buf[i]);
		}
		//cout << "s2c recv : " << len << " << " << s_tmp << endl;
		WXLOG_DEBUG("server recv : [ " << s_tmp << " ]");

		m_client->onSendMessage(recv_buf,len);
//		int isend = send(m_client->GetSocket(), recv_buf, sizeof(recv_buf), 0);
	}

	AppCore* instance = static_cast<AppCore*>(obj);
	instance->stopThreadC2S();
}


void AppCore::stopThreadS2C()
{
	m_server->close();
	runFlag_s2c = false;
}

void AppCore::stopThreadC2S()
{
	m_client->close();
	runFlag_c2s = false;
}