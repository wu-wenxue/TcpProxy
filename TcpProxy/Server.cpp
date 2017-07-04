#include "Server.h"

using namespace wwx;
Server::Server(int port)
{
	m_port = port;
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
		printf("Listen failed:%d", WSAGetLastError());
		return;
	}
}

void Server::Accept()
{
	SOCKADDR_IN addrClient;
	int len = sizeof(SOCKADDR);

	while (1)
	{
		//等待客户请求到来    
		SOCKET sockConn = accept(sockSrv, (SOCKADDR *)&addrClient, &len);
		if (sockConn == SOCKET_ERROR){
			printf("Accept failed:%d", WSAGetLastError());
			break;
		}

		printf("Accept client IP:[%s]\n", inet_ntoa(addrClient.sin_addr));

		//发送数据  
		int iSend = send(sockConn, buf, sizeof(buf), 0);
		if (iSend == SOCKET_ERROR){
			printf("send failed");
			break;
		}

		char recvBuf[100];
		memset(recvBuf, 0, sizeof(recvBuf));
		//      //接收数据  
		recv(sockConn, recvBuf, sizeof(recvBuf), 0);
		printf("%s\n", recvBuf);

		closesocket(sockConn);
	}
}

void Server::onSendMessage(std::string message)
{
	int iSend = send(sockConn, message.c_str(), message.length(), 0);
}

void Server::Close()
{
	closesocket(sockSrv);
	WSACleanup();
}