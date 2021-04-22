#include <iostream>

#include "Client.h"
#include "Server.h"
#include "AppCore.h"
#include "wxlogger_def.h"

using namespace std;
using namespace wxlog;
int main()
{

	Wxlogger* logger = Wxlogger::getInstance();
	SYSTEMTIME st;
	GetLocalTime(&st);
	char szCurTime[64] = { 0 };
	sprintf(szCurTime, "%04d%02d%02d%02d%02d", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute);

	logger->SetLogName(".\\log\\", "TcpProxy_" + string(szCurTime) + ".log");
	logger->SetLogLevel(DEBUG);
	logger->SetLogFileSize(100 * 1024 * 1024);


	WXLOG_INFO("TcpProxy start ...");

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