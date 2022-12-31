#include <string.h>

#include "Socket.h"

using Socket::TCPClient;

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
