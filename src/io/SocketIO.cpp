#include <string>

#include "SocketIO.h"
#include "Socket.h"

using Socket::Packet;

SocketIO::SocketIO(TCPSocket socket)
    : socket(socket) {}

std::string SocketIO::read() {
    return this->socket.recvPacket().toString();
}

void SocketIO::write(const std::string& dataToWrite) {
    Packet packetToSend = Packet(dataToWrite);
    this->socket.sendPacket(packetToSend);
}