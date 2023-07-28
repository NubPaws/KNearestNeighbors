#ifndef _EXECUTION_STOPPED_EXECPTION_H
#define _EXECUTION_STOPPED_EXECPTION_H

#include <exception>
#include <string>

class ExecutionStoppedException : public std::exception {
private:
	std::string message;
public:
	/**
	 * @brief Construct a new Execution Stopped Exception instance.
	 * This instanced is used to notify that an execution in threads
	 * has stopped. That way there is no need to return random data.
	 * 
	 * @param message The message to put in the execption.
	 */
	ExecutionStoppedException(const std::string& message);
	
	const char* what();
};

#endif // _EXECUTION_STOPPED_EXECPTION_H
