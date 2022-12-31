#ifndef _TCP_SOCKET_H
#define _TCP_SOCKET_H

#include <iostream>
#include <netinet/in.h>
#include <vector>
#include <utility>

#include "Types.h"
#include "Packet.h"

namespace Socket {
    enum class Status : size_t {
        Failed, Success
    };

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

    class TCPServer : public TCPSocket {
    private:
        int backlog;
    public:
        /**
         * @brief Construct a new TCPServer object
         *
         * @param port
         * @param ip_address
         * @param backlog number of client connections.
         */
        TCPServer(int port, std::string ip_address, int backlog);
        /**
         * @brief binding server socket
         */
        void bindSocket();
        /**
         * @brief Listen for connections
         */
        void listenForConnections();
        /**
         * @brief Accepts incoming connection
         *
         * @return client socket file descriptor.
         */
        int acceptConnection();
        /**
         * @brief Sending data to client
         *
         * @param clientSocket
         * @param data
         * @return int
         */
        void sendData(int clientSocket, Socket::Packet packet);
        /**
         * @brief Receives data from client
         *
         * @param clientSocket
         * @return Socket::Packet with it being invalid if the connection failed.
         */
        Socket::Packet receiveData(int clientSocket);
        /**
         * @brief handles client requests.
         */
        /**
         * Closing client socket.
        */
        void closeClientConnection(int clientSocket);
    };

    class TCPClient : public TCPSocket {
    public:
        /**
         * @brief sending data to server
         *
         * @param packet A vector of bytes containing the data.
         */
        void sendData(const Socket::Packet& packet);
        /**
         * @brief connecting client to server
         */
        void connectToServer();
        /**
         * @brief Receiving data from server
         *
         * @return Socket::Packet with it being not valid if an error occurred..
         */
        Socket::Packet receiveData();
        /**
         * @brief Construct a new TCPClient object
         *
         * @param port
         * @param ip_address
         */
        TCPClient(int port, std::string ip_address);
    };
}


#endif // _TCP_SOCKET_H
