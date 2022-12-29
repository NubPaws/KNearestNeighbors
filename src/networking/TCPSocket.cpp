#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "TCPSocket.h"
#include "SocketConversion.h"

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

int TCPSocket::sendPacket(int sockfd, const Socket::Packet& packet) {
	int sentBytes;
	size_t size = Socket::toNetwork(packet.size());
	// First send the size of the packet.
	sentBytes = send(sockfd, (byte*)&size, sizeof(size_t), 0);
	if (sentBytes < sizeof(size_t))
		return -1;
	
	// Then send the actual data.
	sentBytes = send(sockfd, packet.getData(), packet.size(), 0);
	if (sentBytes < packet.size())
		return -1;
	
	return 0;
}

Socket::Packet TCPSocket::recvPacket(int sockfd) {
	int status;
	
	size_t size;
	status = recv(sockfd, (byte*)&size, sizeof(size_t), 0);
	
	if (status < 0)
		return Socket::Packet(false);
	else if (status == 0)
		return Socket::Packet(true);
	
	size = Socket::toClient(size);
	
	byte *data = new byte[size];
	status = recv(sockfd, data, size, 0);
	
	if (status < 0)
		return Socket::Packet(false);
	else if (status == 0)
		return Socket::Packet(true);
	
	Socket::Packet packet(data, size);
	
	delete[] data;
	return packet;
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

int TCPClient::sendData(const Socket::Packet& packet) {
	if (sendPacket(socketFileDescriptor, packet) == -1) {
		std::cerr << "Error sending to server" << std::endl;
		return -1;
	}
	return 0;
}

Socket::Packet TCPClient::receiveData() {
	Socket::Packet packet = recvPacket(socketFileDescriptor);
	
	if (!packet.isValid()) {
		std::cerr << strerror(errno) << std::endl;
	}
	return packet;
}
