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
	std::thread t1(&AppCore::ClientToServer, this);
	std::thread t2(&AppCore::ServerToClient, this);
	t1.detach();
	t2.detach();
}

void AppCore::ClientToServer()
{

}

void AppCore::ServerToClient()
{

}