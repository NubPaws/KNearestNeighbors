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
	if (index >= args.size() || !isInt(index))
		return -1;
	return std::stoi(args[index]);
}

double CommandLineArguments::getDouble(const std::size_t& index) const {
	if (index >= args.size() || !isDouble(index))
		return -1;
	return std::stod(args[index]);
}

bool CommandLineArguments::isInt(const std::size_t& index) const {
	return index < args.size() && StringValidator::isInt(args[index]);
}

bool CommandLineArguments::isDouble(const std::size_t& index) const {
	return index < args.size() && StringValidator::isDouble(args[index]);
}

std::size_t CommandLineArguments::size() const {
	return args.size();
}

std::string CommandLineArguments::operator[](const std::size_t& index) const {
	return getStr(index);
}
