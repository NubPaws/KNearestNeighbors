#ifndef _STANDARD_IO_H
#define _STANDARD_IO_H

#include <string>

#include "DefaultIO.h"

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

#endif // _STANDARD_IO_H
