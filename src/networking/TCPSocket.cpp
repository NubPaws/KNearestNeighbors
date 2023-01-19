#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "Socket.h"
#include "SocketConversion.h"

using namespace Socket;

std::string SOCKET_CREATION_ERROR = "Error creating socket";
std::string DATA_SENDING_ERROR = "Error sending data";

TCPSocket::TCPSocket(int port, std::string ip_address) {
    this->port = port;
    this->ip_address = ip_address;
	this->socketFileDescriptor = socket(AF_INET, SOCK_STREAM, 0);
    if (this->socketFileDescriptor < 0) {
		std::cerr << SOCKET_CREATION_ERROR << std::endl;
        throw std::runtime_error(SOCKET_CREATION_ERROR);
    }
    memset(&(this->socketAddress), 0, sizeof(this->socketAddress));
	this->socketAddress.sin_family = AF_INET;
	this->socketAddress.sin_addr.s_addr = inet_addr(this->ip_address.c_str());
	this->socketAddress.sin_port = htons(this->port);
}

TCPSocket::TCPSocket(int socketFileDescriptor) {
	this->socketFileDescriptor = socketFileDescriptor;
}

void TCPSocket::closeSocket() {
    close(this->socketFileDescriptor);
}

void TCPSocket::sendPacket(const Socket::Packet& packet) {
	int sentBytes;
	size_t size = Socket::toNetwork(packet.size());
	// First send the size of the packet.
	sentBytes = send(this->socketFileDescriptor, (byte*)&size, sizeof(size_t), 0);
	if (sentBytes < sizeof(size_t)) {
		throw std::runtime_error(DATA_SENDING_ERROR);
	}
	
	// Then send the actual data.
	size_t offset = 0;
	while (offset < packet.size()) {
		sentBytes = send(this->socketFileDescriptor, packet.getData() + offset, packet.size() - offset, 0);
		if (sentBytes < 0)
			throw std::runtime_error(DATA_SENDING_ERROR);
		offset += sentBytes;
	}
}

Socket::Packet TCPSocket::recvPacket() {
	int status;
	
	size_t size;
	status = recv(this->socketFileDescriptor, (byte*)&size, sizeof(size_t), 0);
	
	if (status < 0)
		return Socket::Packet(false);
	else if (status == 0)
		return Socket::Packet(true);
	
	size = Socket::toClient(size);
	
	byte *data = new byte[size];
	
	size_t offset = 0;
	while (offset < size) {
		status = recv(this->socketFileDescriptor, data + offset, size - offset, 0);
		if (status < 0)
			return Socket::Packet(false);
		offset += status;
	}
	
	Socket::Packet packet(data, size);
	
	delete[] data;
	return packet;
}

bool TCPSocket::isValidSocket() {
	return this->socketFileDescriptor != -1;
}
