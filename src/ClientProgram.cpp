#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#include "TCPSocket.h"

int main(int argc, char const *argv[])
{
	TCPClient tcpClient(1234, "127.0.0.1");
	tcpClient.initSocket();
	tcpClient.sendData("Hey");
	tcpClient.closeSocket();

	return 0;
}