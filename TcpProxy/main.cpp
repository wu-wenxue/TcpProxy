#include <iostream>

#include "Client.h"
#include "Server.h"
#include "AppCore.h"

using namespace std;

int main()
{
<<<<<<< HEAD
	wwx::Client* client = new wwx::Client("10.33.1.2", 50010);
	wwx::Server* server = new wwx::Server(50010);
=======
	wwx::Client* client = new wwx::Client("127.0.0.1", 60000);
	wwx::Server* server = new wwx::Server(5000);
>>>>>>> 3a7a0e421f8ef55c8db2300e7d4d89cbfc258052

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