#include "ExecutionStoppedException.h"

ExecutionStoppedException::ExecutionStoppedException(const std::string& msg)
	: message(msg) {
	
}

const char* ExecutionStoppedException::what() {
	return message.c_str();
}
