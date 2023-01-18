#ifndef _TCP_CLIENT_H
#define _TCP_CLIENT_H

#include "TCPSocket.h"
#include "Packet.h"

using Socket::TCPSocket;

namespace Socket
{
    class TCPClient : public TCPSocket {
    public:
        /**
         * @brief connecting client to server
         */
        void connectToServer();
        /**
         * @brief Receiving data from server
         *
         * @return Socket::Packet with it being not valid if an error occurred..
         */
        TCPClient(int port, std::string ip_address);
    };
}


#endif /* _TCP_CLIENT_H */
