#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#include "TCPSocket.h"
#include "Types.h"

int main(int argc, char const *argv[]) {
	// Setting up server
	TCPServer tcpServer(1234, "127.0.0.1", 5);
	byte buffer[4096];
	tcpServer.initSocket();
	tcpServer.bindSocket();
	tcpServer.listenForConnections();

	int clientSocket = tcpServer.acceptConnection();
	tcpServer.receiveData(clientSocket, buffer, sizeof(buffer));
	std::cout << buffer << std::endl;

	tcpServer.sendData(clientSocket, buffer, sizeof(buffer));
	tcpServer.closeClientConnection(clientSocket);
	tcpServer.closeSocket();

	return 0;
}
