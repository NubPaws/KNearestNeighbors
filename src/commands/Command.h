#ifndef _COMMAND_H
#define _COMMAND_H

#include <string>

#include "DefaultIO.h"

class Command {
private:
	std::string description;
	DefaultIO *dio;
	
public:
	Command();
	Command(std::string desc, DefaultIO *io);
	
	Command(const Command& command) = delete;
	Command& operator=(const Command& command) = delete;
	
	Command(Command&& command) = delete;
	Command& operator=(Command&& command) = delete;
	
	virtual ~Command();
	
	virtual void execute() = 0;
	
	std::string getDescription() const;
	void setDescription(const std::string& desc);
};

#endif // _COMMAND_H