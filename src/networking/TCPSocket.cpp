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
		std::cerr << "Error creating socket" << std::endl;
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

int TCPServer::bindSocket() {
    int bindReturnCode = bind(this->socketFileDescriptor,
							  (struct sockaddr*)&(this->socketAddress),
							  sizeof(this->socketAddress));
    if (bindReturnCode < 0) {
		std::cerr << "Error binding socket" <<std::endl;
        return -1;
    }
	return 0;
}

int TCPServer::listenForConnections() {
    int listenReturnCode = listen(this->socketFileDescriptor, this->backlog);
	if (listenReturnCode < 0) {
		std::cerr << "Error listening to a socket" <<std::endl;
        return -1;
	}
    return 0;
}

int TCPServer::handleClient() {
    struct sockaddr_in clientAddress;

	unsigned int addressLength = sizeof(clientAddress);
	int clientSocket = accept(this->socketFileDescriptor, (struct sockaddr*)&clientAddress, &addressLength);
	if (clientSocket < 0) {
		std::cerr << "Error accepting client" << std::endl;
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
		std::cout << "Server received " << buffer << " from user" << std::endl;
	}

	std::cout << "Server sending " << buffer << " to user" << std::endl;
	int sent_bytes = send(clientSocket, buffer, readBytes, 0);
	if (sent_bytes < 0) {
		std::cerr << "Error sending to client" << std::endl;
        return -1;
	}

    close(clientSocket);

    return 0;
}

TCPClient::TCPClient(int port, std::string ip_address) : TCPSocket(port, ip_address) {}

int TCPClient::connectToServer() {
    int connectReturnCode = connect(this->socketFileDescriptor,
									(struct sockaddr*)&(this->socketAddress),
									sizeof(this->socketAddress));
    if (connectReturnCode < 0) {
		std::cerr << "Error connecting to server" << std::endl;
        return -1;
	}
	return 0;
}

int TCPClient::sendData(std::string data) {
    int dataLength = data.length();
	std::cout << "client is sending: " << data << std::endl;
    int sentBytes = send(this->socketFileDescriptor, data.c_str(), dataLength, 0);

	if (sentBytes < 0)	{
		// error
        return -1;
	}
	char buffer[4096];
    int expectedDataLength = sizeof(buffer);
    int readBytes = recv(this->socketFileDescriptor, buffer, expectedDataLength, 0);
	if (readBytes == 0) {
		// connection is closed
	}
	else if (readBytes < 0) {
		// error
        return -1;
	}
	else {
		std::cout << "Client received: " << buffer << " from server" << std::endl;
	}
	return 0;
}