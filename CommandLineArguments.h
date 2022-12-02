#ifndef _COMMAND_LINE_ARGUMENTS_H
#define _COMMAND_LINE_ARGUEMNTS_H

#include <string>
#include <vector>
#include <cstddef>

class CommandLineArguments {
private:
	std::vector<std::string> args;
public:
	CommandLineArguments(const int& argc, const char **argv);
	
	std::string getStr(const size_t& index) const;
	int getInt(const size_t& index) const;
	double getDouble(const std::size_t& index) const;
	
	std::size_t size() const;
	std::string operator[](const size_t& index) const;
};

#endif // _COMMAND_LINE_ARGUEMNTS_H
