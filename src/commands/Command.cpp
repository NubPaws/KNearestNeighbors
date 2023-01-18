#include "Command.h"

Command::Command(const std::string& desc, DefaultIO& io)
	: description(desc), io(io) {
	
}

std::string Command::getDescription() const {
	return description;
}

void Command::setDescription(const std::string& desc) {
	this->description = desc;
}
