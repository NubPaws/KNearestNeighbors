#ifndef _DEFAULT_IO_H
#define _DEFAULT_IO_H

#include <string>

#include "Socket.h"

using Socket::TCPSocket;

class DefaultIO {
public:
	virtual std::string read() = 0;
	virtual void write(const std::string& dataToWrite) = 0;
};

class StandardIO : public DefaultIO {
public:
	/**
	 * @brief Reads from standard input.
	 * @return std::string
	 */
	std::string read() override;

	/**
	 * @brief Writing data using standardIO
	 * @param dataToWrite
	 */
	void write(const std::string& dataToWrite) override;
};

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

#endif // _DEFAULT_IO_H
