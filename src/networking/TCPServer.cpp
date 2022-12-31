#include <string.h>
#include <unistd.h>

#include "Socket.h"

using Socket::TCPServer;

std::string SOCKET_BINDING_ERROR = "Error binding socket";
std::string SOCKET_LISTEN_ERROR = "Error listening to a socket";
std::string SOCKET_ACCEPT_ERROR = "Error accepting client";

TCPServer::TCPServer(int port, std::string ip_address, int backlog) : TCPSocket(port, ip_address) {
    this->backlog = backlog;
}

void TCPServer::bindSocket() {
    int bindReturnCode = bind(this->socketFileDescriptor,
							  (struct sockaddr*)&(this->socketAddress),
							  sizeof(this->socketAddress));
    if (bindReturnCode < 0) {
		throw std::runtime_error(SOCKET_BINDING_ERROR);
    }
}

void TCPServer::listenForConnections() {
    int listenReturnCode = listen(this->socketFileDescriptor, this->backlog);
	if (listenReturnCode < 0) {
		throw std::runtime_error(SOCKET_LISTEN_ERROR);
	}
}

int TCPServer::acceptConnection() {
	struct sockaddr_in clientAddress;
	unsigned int addressLength = sizeof(clientAddress);
	int clientSocket = accept(this->socketFileDescriptor, (struct sockaddr*)&clientAddress, &addressLength);
	if (clientSocket < 0) {
		throw std::runtime_error(SOCKET_ACCEPT_ERROR);
	}
	return clientSocket;
}

void TCPServer::sendData(int clientSocket, Socket::Packet packet) {
	try {
		sendPacket(clientSocket, packet);
	}
	catch (std::exception exception) {
		throw exception;
	}
}

Socket::Packet TCPServer::receiveData(int clientSocket) {
	Socket::Packet packet = recvPacket(clientSocket);
	
	if (!packet.isValid())
		std::cerr << strerror(errno) << std::endl;
	return packet;
}

void TCPServer::closeClientConnection(int clientSocket) {
	close(clientSocket);
}