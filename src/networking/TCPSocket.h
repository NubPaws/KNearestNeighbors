#ifndef _TCP_SOCKET_H
#define _TCP_SOCKET_H

#include <netinet/in.h>

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
         * @brief initialize socket.
         */
        void initSocket();
        
        /**
         * @brief closing TCP socket.
         */
        void closeSocket();
    protected:
        /**
         * @brief Sends a Socket::Packet over a socket file descriptor.
        */
        void sendPacket(int sockfd, const Socket::Packet& packet);
        /**
         * @brief Receives a Socket::Packet from a file descriptor.
         * 
         * @return Socket::Packet with the data that was received.
        */
        Socket::Packet recvPacket(int sockfd);
    };
}

#endif /* _TCP_SOCKET_H */
