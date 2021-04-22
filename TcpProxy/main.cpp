#include <iostream>

#include "Client.h"
#include "Server.h"
#include "AppCore.h"

using namespace std;

int main()
{

	wwx::Client* client = new wwx::Client("127.0.0.1", 50051);
	wwx::Server* server = new wwx::Server(5000);

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