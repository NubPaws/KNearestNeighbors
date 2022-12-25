#ifndef TCP_SOCKET_H
#define TCP_SOCKET_H

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
    virtual int initSocket();
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
    int initSocket() override;
    /**
     * @brief handles client requests.
     */
    int handleClient();
};

class TCPClient : public TCPSocket {
    public:
    int initSocket() override;
    /**
     * @brief sending data to server
     *
     * @param data
     */
    int sendData(std::string data);
    TCPClient(int port, std::string ip_address);
};

#endif /* TCP_SOCKET_H */
