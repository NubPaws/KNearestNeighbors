#ifndef _DEFAULT_IO_H
#define _DEFAULT_IO_H

#include <string>

class DefaultIO {
public:
	virtual std::string read() = 0;
	virtual void write(const std::string& dataToWrite) = 0;
};

#endif // _DEFAULT_IO_H
