#pragma once
#include "Client.h"
#include "Server.h"


class AppCore
{
public:
	AppCore();
	~AppCore();

	void RegisterClient(wwx::Client* client);
	void RegisterServer(wwx::Server* server);

	void start();

	void ClientToServer();
	void ServerToClient();

private:
	wwx::Client* m_client;
	wwx::Server* m_server;

};

