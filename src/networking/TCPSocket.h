#ifndef _TCP_SOCKET_H
#define _TCP_SOCKET_H

#include <iostream>
#include <netinet/in.h>

#include "Types.h"

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
     *
     * @return 0 on success, -1 otherwise.
     */
    int initSocket();

    int sendData(byte data[]);
    /**
     * @brief closing TCP socket.
     *
     */
    void closeSocket();
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
     *
     * @return 0 on success, -1 otherwise.
     */
    int bindSocket();
    /**
     * @brief Listen for connections
     *
     * @return 0 on success, -1 otherwise.
     */
    int listenForConnections();
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
    int sendData(int clientSocket, byte data[], size_t dataLength);
    /**
     * @brief Receives data from client
     *
     * @param clientSocket
     * @param inputBuffer
     * @return int
     */
    int receiveData(int clientSocket, byte inputBuffer[], size_t expectedDataLength);
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
     * @param data
     * @param dataLength
     */
    int sendData(byte data[], size_t dataLength);
    /**
     * @brief connecting client to server
     *
     * @return 0 on success, -1 otherwise.
     */
    int connectToServer();
    /**
     * @brief Receiving data from server
     *
     * @param inputBuffer
     * @param expectedDataLength
     * @return 0 on success, -1 otherwise.
     */
    int receiveData(byte inputBuffer[], size_t expectedDataLength);
    /**
     * @brief Construct a new TCPClient object
     *
     * @param port
     * @param ip_address
     */
    TCPClient(int port, std::string ip_address);
};

#endif /* _TCP_SOCKET_H */
