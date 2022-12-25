#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "TCPSocket.h"

TCPSocket::TCPSocket(int port, std::string ip_address) {
    this->port = port;
    this->ip_address = ip_address;
}

int TCPSocket::initSocket() {
    this->socketFileDescriptor = socket(AF_INET, SOCK_STREAM, 0);
    if (this->socketFileDescriptor < 0) {
        perror("error creating socket");
        return -1;
    }
    memset(&(this->socketAddress), 0, sizeof(this->socketAddress));
	this->socketAddress.sin_family = AF_INET;
	this->socketAddress.sin_addr.s_addr = inet_addr(this->ip_address.c_str());
	this->socketAddress.sin_port = htons(this->port);
    return 0;
}

void TCPSocket::closeSocket() {
    close(this->socketFileDescriptor);
}

TCPServer::TCPServer(int port, std::string ip_address, int backlog) : TCPSocket(port, ip_address) {
    this->backlog = backlog;
}

int TCPServer::initSocket() {
    TCPSocket::initSocket();
    int bindReturnCode = bind(this->socketFileDescriptor, (struct sockaddr*)&(this->socketAddress), sizeof(this->socketAddress));
    if (bindReturnCode < 0) {
		perror("error binding socket");
        return -1;
    }
    int listenReturnCode = listen(this->socketFileDescriptor, this->backlog);
	if (listenReturnCode< 0) {
		perror("error listening to a socket");
        return -1;
	}
    return 0;
}

int TCPServer::handleClient() {
    struct sockaddr_in clientAddress;

	unsigned int addressLength = sizeof(clientAddress);
	int clientSocket = accept(this->socketFileDescriptor, (struct sockaddr*)&clientAddress, &addressLength);
	if (clientSocket < 0) {
		perror("error accepting client");
        return -1;
	}

	char buffer[4096];
	int expectedDataLength = sizeof(buffer);
	int readBytes = recv(clientSocket, buffer, expectedDataLength, 0);
	if (readBytes == 0) {
		// connection is closed
	}
	else if (readBytes < 0) {
			// error
	}
	else {
		std::cout << buffer;
	}
	int sent_bytes = send(clientSocket, buffer, readBytes, 0);
	if (sent_bytes < 0) {
		perror("error sending to client");
        return -1;
	}

    close(clientSocket);

    return 0;
}
