#ifndef SOCKET_H
#define SOCKET_H

#include <iostream>
#include <netinet/in.h>
#include <vector>
#include <utility>

#include "Types.h"
#include "Packet.h"
#include "TCPSocket.h"
#include "TCPServer.h"
#include "TCPClient.h"

namespace Socket {
    enum class Status : size_t {
        Failed, Success
    };
}


#endif // SOCKET_H
