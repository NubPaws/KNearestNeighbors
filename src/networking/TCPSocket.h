#ifndef _TCP_SOCKET_H
#define _TCP_SOCKET_H

#include <iostream>
#include <netinet/in.h>

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
     * @brief handles client requests.
     */
    int handleClient();
};

class TCPClient : public TCPSocket {
    public:
    /**
     * @brief sending data to server
     *
     * @param data
     */
    int sendData(std::string data);
    /**
     * @brief connecting client to server
     *
     * @return 0 on success, -1 otherwise.
     */
    int connectToServer();
    /**
     * @brief Construct a new TCPClient object
     *
     * @param port
     * @param ip_address
     */
    TCPClient(int port, std::string ip_address);
};

#endif /* _TCP_SOCKET_H */
