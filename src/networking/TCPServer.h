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
         * @return client socket.
         */
        TCPSocket acceptConnection();
        /**
         * @brief handles client requests.
         */
    };   
}


#endif /* _TCP_SERVER_H */
