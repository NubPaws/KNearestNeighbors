#include <string.h>

#include "Socket.h"

using Socket::TCPClient;

std::string SOCKET_CONNECT_ERROR = "Error connecting to server";


TCPClient::TCPClient(int port, std::string ip_address) : TCPSocket(port, ip_address) {}

void TCPClient::connectToServer() {
    int connectReturnCode = connect(this->socketFileDescriptor,
									(struct sockaddr*)&(this->socketAddress),
									sizeof(this->socketAddress));
    if (connectReturnCode < 0) {
		throw std::runtime_error(SOCKET_CONNECT_ERROR);
	}
}

void TCPClient::sendData(const Socket::Packet& packet) {
    try {
        sendPacket(socketFileDescriptor, packet);
    }
    catch (std::exception exception) {
        throw exception;
    }
}

Socket::Packet TCPClient::receiveData() {
	Socket::Packet packet = recvPacket(socketFileDescriptor);
	
	if (!packet.isValid()) {
		std::cerr << strerror(errno) << std::endl;
	}
	return packet;
}
