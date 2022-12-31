#include <string.h>
#include <unistd.h>

#include "Socket.h"

using Socket::TCPServer;

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

int TCPServer::acceptConnection() {
	struct sockaddr_in clientAddress;
	unsigned int addressLength = sizeof(clientAddress);
	int clientSocket = accept(this->socketFileDescriptor, (struct sockaddr*)&clientAddress, &addressLength);
	if (clientSocket < 0) {
		std::cerr << "Error accepting client" << std::endl;
        return -1;
	}
	return clientSocket;
}

int TCPServer::sendData(int clientSocket, Socket::Packet packet) {
	int status = sendPacket(clientSocket, packet);
	if (status == -1) {
		std::cerr << "Error sending to client" << std::endl;
        return -1;
	}
	return 0;
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