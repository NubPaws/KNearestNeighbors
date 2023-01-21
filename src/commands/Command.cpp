#include "Command.h"

const std::string Command::ERROR_SYMBOL = "[ERR]";

Command::Command(const std::string& desc, DefaultIO* io)
	: description(desc), io(io) {
	
}

std::string Command::getDescription() const {
	return description;
}

void Command::setDescription(const std::string& desc) {
	this->description = desc;
}
