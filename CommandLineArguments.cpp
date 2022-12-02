#include "CommandLineArguments.h"
#include "StringValidator.h"

CommandLineArguments::CommandLineArguments(const int& argc, const char **argv) : args(argc) {
	for (int i = 0; i < argc; i++)
		args.push_back(std::string(argv[i]));
}

std::string CommandLineArguments::getStr(const std::size_t& index) const {
	if (index >= args.size())
		return "";
	return args[index];
}

int CommandLineArguments::getInt(const std::size_t& index) const {
	if (index >= args.size() || StringValidator::isInt(args[index]))
		return -1;
	return std::stoi(args[index]);
}

double CommandLineArguments::getDouble(const std::size_t& index) const {
	if (index >= args.size() || StringValidator::isDouble(args[index]))
		return -1;
	return std::stod(args[index]);
}

std::size_t CommandLineArguments::size() const {
	return args.size();
}

std::string CommandLineArguments::operator[](const std::size_t& index) const {
	return getStr(index);
}
