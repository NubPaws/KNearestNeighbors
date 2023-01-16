#ifndef _TCP_SERVER_H
#define _TCP_SERVER_H

//using Socket::T

namespace Socket
{
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
}


#endif /* _TCP_SERVER_H */
