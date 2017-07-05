#include <iostream>

#include "Client.h"
#include "Server.h"
#include "AppCore.h"

using namespace std;

int main()
{
	wwx::Client* client = new wwx::Client("10.33.1.2", 50010);
	wwx::Server* server = new wwx::Server(50010);

	AppCore* app = new AppCore();

	app->RegisterClient(client);
	app->RegisterServer(server);

	app->start();

	while (1)
	{
		string cmd;
		cin >> cmd;
		if (cmd == "quit")
			break;
	}


	return 0;

}