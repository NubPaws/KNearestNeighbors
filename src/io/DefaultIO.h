#ifndef _DEFAULT_IO_H
#define _DEFAULT_IO_H

#include <string>

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
	std::string read();

	/**
	 * @brief Writing data using standardIO
	 * @param dataToWrite
	 */
	void write(const std::string& dataToWrite);
};

#endif // _DEFAULT_IO_H
