#ifndef _COMMAND_LINE_ARGUMENTS_H
#define _COMMAND_LINE_ARGUEMNTS_H

#include <string>
#include <vector>
#include <cstddef>

class CommandLineArguments {
private:
	std::vector<std::string> args;
public:
	/**
	 * @brief Construct a new Command Line Arguments object
	 * 
	 * @param argc The number of command line arguments.
	 * @param argv The command line arguments themselves.
	 */
	CommandLineArguments(const int& argc, const char **argv);
	
	/**
	 * @brief Get the argument at a specific index as an string.
	 * 
	 * @param index The index of the argument (0 is the name of the program).
	 * @return std::string The argument.
	 */
	std::string getStr(const size_t& index) const;
	/**
	 * @brief Get the argument at a specific index as an int.
	 * 
	 * @param index The index of the argument (0 is the name of the program).
	 * @return int The argument.
	 */
	int getInt(const size_t& index) const;
	/**
	 * @brief Get the argument at a specific index as an double.
	 * 
	 * @param index The index of the argument (0 is the name of the program).
	 * @return double The argument.
	 */
	double getDouble(const std::size_t& index) const;
	
	/**
	 * @brief Get the number of arguments given.
	 * 
	 * @return std::size_t The number of arguments given.
	 */
	std::size_t size() const;
	/**
	 * @brief Operator overloading for the function getStr.
	 * 
	 * @param index The index of the argument (0 is the name of the program).
	 * @return std::string The argument.
	 */
	std::string operator[](const size_t& index) const;
};

#endif // _COMMAND_LINE_ARGUEMNTS_H
