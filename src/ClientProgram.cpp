#include <iostream>
#include <vector>
#include <string>
#include <sstream>

#include "CommandLineArguments.h"
#include "Types.h"
#include "Socket.h"
#include "VectorDistance.h"
#include "StringValidator.h"
#include "Packet.h"

using Socket::TCPClient;

std::string FAILED_SERVER_CONNECTION = "Failed to connect to server";

/**
 * @brief Reads the next line from the user and converts it to a vector of strings.
 * 
 * @return std::vector<std::string> Where each entry is the data (delimited by spaces).
*/
static std::vector<std::string> readLineAsVector() {
	std::string line;
	std::getline(std::cin, line);
	std::istringstream iss(line);
	
	std::vector<std::string> result;
	
	std::string str;
	while (iss >> str)
		result.push_back(str);
	
	return result;
}

/**
 * @brief Validates the input of the user.
 * 
 * @return bool Whether the input is valid or not.
*/
static bool isInputValid(std::vector<std::string> line) {
	switch (line.size()) {
	case 1:
		return line[0] == "-1";
	case 0:
	case 2:
		return false;
	}
	
	if (!Utils::isInt(line[line.size() - 1]))
		return false;
	
	using VectorDistance::Calculator;
	
	if (Calculator::getType(line[line.size() - 2]) == Calculator::Type::Empty)
		return false;
	
	for (int i = 0; i < line.size() - 2; i++)
		if (!Utils::isDouble(line[i]))
			return false;
	
	return true;
}

/**
 * @brief Given the line the user entered, converts it into a packet that we
 * can send out.
 * 
 * @return The packet to be sent.
*/
static Socket::Packet generatePacket(std::vector<std::string>& line) {
	using VectorDistance::Calculator;
	
	int k;
	Calculator::Type type;
	Vector vec;
	
	// Get the k.
	k = std::stoi(line[line.size() - 1]);
	line.pop_back();
	// Get the calculation type.
	type = Calculator::getType(line[line.size() - 1]);
	line.pop_back();
	
	std::ostringstream out;
	for (const std::string& str : line)
		out << str << " ";
	
	out << (size_t)type << " " << k;
	
	return Socket::Packet(out.str());
}

int main(int argc, const char *argv[]) {
	// Load the command line arguments and validate the data.
	CommandLineArguments args(argc, argv);
	
	const size_t ipIndex = 1;
	const size_t portIndex = 2;
	
	if (args.size() < 3 || !args.isInt(portIndex)) {
		std::cout << "Invalid use of the command.\n"
			<< "Usage: " << args[0] << " [ip] [port]" << std::endl;
		return 0;
	}
	
	// Get the ip and port.
	std::string ip = args[ipIndex];
	const int port = args.getInt(portIndex);
	
	// Initialize the client socket to do the connection.
	TCPClient tcpClient(port, ip);
	try {
		tcpClient.connectToServer();
	}
	catch (...) {
		std::cerr << FAILED_SERVER_CONNECTION << std::endl;
	}
	
	std::cout << tcpClient.receiveData().toString();
	
	// When all's said and done, close the connection.
	tcpClient.closeSocket();
	
	return 0;
}
