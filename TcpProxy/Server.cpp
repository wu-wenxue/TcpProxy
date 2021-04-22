#include "Server.h"
#include <iostream>

using namespace wwx;
using namespace std;

Server::Server(int port)
{
	m_port = port;
	Init();
	Bind();
	Listen();
}


Server::~Server()
{
}

void Server::Init()
{
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		printf("Failed to load Winsock");
		return;
	}

	//创建用于监听的套接字  
	sockSrv = socket(AF_INET, SOCK_STREAM, 0);

	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(m_port); //1024以上的端口号  
	addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);

}

void Server::Bind()
{
	int retVal = bind(sockSrv, (LPSOCKADDR)&addrSrv, sizeof(SOCKADDR_IN));
	if (retVal == SOCKET_ERROR){
		printf("Failed bind:%d\n", WSAGetLastError());
		return;
	}
}

void Server::Listen()
{
	if (listen(sockSrv, 10) == SOCKET_ERROR){
		printf("Listen failed:%d \n", WSAGetLastError());
		return;
	}
}

bool Server::Accept()
{
	//SOCKADDR_IN addrClient;
	int len = sizeof(SOCKADDR);
	memset(&addrClient, 0x00, len);
	//等待客户请求到来    
	sockConn = accept(sockSrv, (SOCKADDR *)&addrClient, &len);
	if (sockConn == SOCKET_ERROR){
		printf("Accept failed:%d", WSAGetLastError());
		return false;
	}
	printf("Accept client IP:[%s]\n", inet_ntoa(addrClient.sin_addr));
	return true;
}

bool Server::onSendMessage(char* message,int len)
{
	int iSend = send(sockConn, message, len, 0);
	cout << " server send : " << iSend << endl;
	return true;
}

void Server::close()
{
	closesocket(sockSrv);
	WSACleanup();
}

SOCKET Server::GetClientSocket()
{
	return sockConn;
}