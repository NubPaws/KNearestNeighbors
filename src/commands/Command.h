#ifndef _COMMAND_H
#define _COMMAND_H

#include <string>

#include "DefaultIO.h"

class Command {
public:
	static const std::string ERROR_SYMBOL;
private:
	std::string description;
protected:
	DefaultIO *io;
public:
	/**
	 * @brief Construct a new Command object.
	 * 
	 * @param desc The description of the command.
	 * @param io The IO object to write to and read from.
	 */
	Command(const std::string& desc, DefaultIO* io);
	
	/**
	 * @brief Executes the command.
	 */
	virtual void execute() = 0;
	
	/**
	 * @brief Get the description.
	 * 
	 * @return std::string The description.
	 */
	std::string getDescription() const;
	/**
	 * @brief Set the description.
	 * 
	 * @param desc The new description.
	 */
	void setDescription(const std::string& desc);
};

#endif // _COMMAND_H