#include "CommandLineArguments.h"
#include "StringValidator.h"
#include "Types.h"

CommandLineArguments::CommandLineArguments(const int& argc, const char **argv) : args() {
	for (int i = 0; i < argc; i++)
		args.push_back(std::string(argv[i]));
}

std::string CommandLineArguments::getStr(const size_t& index) const {
	if (index >= args.size())
		return "";
	return args[index];
}

int CommandLineArguments::getInt(const size_t& index) const {
	if (index >= args.size() || !isInt(index))
		return -1;
	return std::stoi(args[index]);
}

double CommandLineArguments::getDouble(const size_t& index) const {
	if (index >= args.size() || !isDouble(index))
		return -1;
	return std::stod(args[index]);
}

bool CommandLineArguments::isInt(const size_t& index) const {
	return index < args.size() && StringValidator::isInt(args[index]);
}

bool CommandLineArguments::isDouble(const size_t& index) const {
	return index < args.size() && StringValidator::isDouble(args[index]);
}

size_t CommandLineArguments::size() const {
	return args.size();
}

std::string CommandLineArguments::operator[](const size_t& index) const {
	return getStr(index);
}
