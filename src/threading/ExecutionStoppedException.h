#ifndef _EXECUTION_STOPPED_EXECPTION_H
#define _EXECUTION_STOPPED_EXECPTION_H

#include <exception>
#include <string>

class ExecutionStoppedException : public std::exception {
private:
	std::string message;
public:
	ExecutionStoppedException(const std::string& message);
	
	const char* what();
};

#endif // _EXECUTION_STOPPED_EXECPTION_H
