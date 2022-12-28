#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#include "Types.h"
#include "TCPSocket.h"

int main(int argc, char const *argv[])
{
	TCPClient tcpClient(1234, "127.0.0.1");
	tcpClient.initSocket();
	tcpClient.connectToServer();

	byte message[] = "Hello";
	tcpClient.sendData(message, sizeof(message));
	std::cout << "Client is sending: " << message << std::endl;

	byte serverRespose[4096];
	tcpClient.receiveData(serverRespose, sizeof(serverRespose));
	std::cout << "Client received: " << message << std::endl;
	tcpClient.closeSocket();

	return 0;
}
