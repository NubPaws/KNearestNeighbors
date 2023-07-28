#ifndef _SOCKET_IO_H
#define _SOCKET_IO_H

#include <string>

#include "DefaultIO.h"
#include "Socket.h"

class SocketIO : public DefaultIO {
private:
	TCPSocket socket;
public:
	/**
	 * @brief Construct a new SocketIO object
	 * @param socket
	 */
	SocketIO(TCPSocket socket);
	/**
	 * @brief Reads from socket.
	 * @return std::string
	 */
	std::string read() override;

	/**
	 * @brief Writing data to socket
	 * @param dataToWrite
	 */
	void write(const std::string& dataToWrite) override;
};

#endif // _SOCKET_IO_H
