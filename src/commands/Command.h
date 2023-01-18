#ifndef _COMMAND_H
#define _COMMAND_H

#include <string>

#include "DefaultIO.h"

class Command {
private:
	std::string description;
protected:
	DefaultIO &io;
public:
	Command(const std::string& desc, DefaultIO& io);
	
	virtual void execute() = 0;
	
	std::string getDescription() const;
	void setDescription(const std::string& desc);
};

#endif // _COMMAND_H