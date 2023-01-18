#ifndef _TCP_SOCKET_H
#define _TCP_SOCKET_H

#include <netinet/in.h>
#include <string>

#include "Packet.h"

namespace Socket {
class TCPSocket {
    protected:
        int socketFileDescriptor;
        struct sockaddr_in socketAddress;
        private:
        int port;
        std::string ip_address;

    public:
        /**
         * @brief TCPSocket constructor
         * @param port port number
         * @param ip_address
         */
        TCPSocket(int port, std::string ip_address);

        /**
         * @brief Construct a new TCPSocket object based on existing file descriptor
         * @param socketFileDescriptor
         */
        TCPSocket(int socketFileDescriptor);
        
        /**
         * @brief closing TCP socket.
         */
        void closeSocket();
        /**
         * @brief Sends a Socket::Packet over a socket file descriptor.
        */
        void sendPacket(const Socket::Packet& packet);
        /**
         * @brief Receives a Socket::Packet from a file descriptor.
         * 
         * @return Socket::Packet with the data that was received.
        */
        Socket::Packet recvPacket();
        bool isValidSocket();
    };
}

#endif /* _TCP_SOCKET_H */
