#pragma once
#include "Client.h"
#include "Server.h"
#include <vector>
#include <string>
#include <list>


class AppCore
{
public:
	AppCore();
	~AppCore();

	void RegisterClient(wwx::Client* client);
	void RegisterServer(wwx::Server* server);

	void start();

	void ClientToServer(void* obj);
	void ServerToClient(void* obj);

	void stopThreadS2C();
	void stopThreadC2S();

private:
	wwx::Client* m_client;
	wwx::Server* m_server;

	std::vector<std::string> vec_c2s;
	std::vector<std::string> vec_s2c;

	bool runFlag_s2c, runFlag_c2s;

};

