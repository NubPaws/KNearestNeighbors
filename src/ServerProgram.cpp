#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#include "TCPSocket.h"

int main(int argc, char const *argv[]) {
	TCPServer tcpServer(1234, "127.0.0.1", 5);
	tcpServer.initSocket();
	tcpServer.bindSocket();
	tcpServer.listenForConnections();
	tcpServer.handleClient();
	tcpServer.closeSocket();

	return 0;
}
