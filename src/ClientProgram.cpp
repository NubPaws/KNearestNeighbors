#include <iostream>
#include <ios>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

#include "CommandLineArguments.h"
#include "Types.h"
#include "Socket.h"
#include "VectorDistance.h"
#include "StringValidator.h"
#include "Packet.h"
#include "CommandClasses.h"

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

void optionAlgorithmSettings(Socket::TCPClient& client) {
	client.sendPacket("2");
	
	std::cout << client.recvPacket().toString();
	
	std::string line;
	std::getline(std::cin, line);
	client.sendPacket(line);
}

#include "SocketConversion.h"

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
		return 0;
	}
	
	std::string input;
	int option;
	bool keepSending = true;
	while (keepSending) {
		// Read the menu from the server.
		std::cout << tcpClient.recvPacket().toString();
		
		std::getline(std::cin, input);
		
		if (!Utils::isInt(input)) {
			std::cout << "wrong input.\n";
			continue;
		}
		
		option = std::stoi(input);
		
		switch (option) {
		case 1: {
			// Send the number to server to start the command.
			tcpClient.sendPacket(input);
			std::string path;
			
			// Read the message, to upload the first file, from the server.
			std::cout << tcpClient.recvPacket().toString();
			// Read the path of the file.
			std::getline(std::cin, path);
			
			std::ifstream inFile;
			// Open the file.
			inFile.open(path);
			
			// Check that the file has opened successfully.
			if (!inFile.is_open()) {
				std::cout << "invalid file\n";
				break;
			}
			
			std::stringstream buffer;
			// Read the entire file into a buffer.
			buffer << inFile.rdbuf();
			// Close the file.
			inFile.close();
			
			// Send the data from the file to the server.
			tcpClient.sendPacket(buffer.str());
			// Clear the buffer.
			buffer.str(std::string());
			// Receive the "upload done" message from the server.
			std::cout << tcpClient.recvPacket().toString();
			
			// Read the message, to upload the second (test) file, from the server.
			std::cout << tcpClient.recvPacket().toString();
			
			// Read the path for the second file.
			std::getline(std::cin, path);
			// Open the second file.
			inFile.open(path);
			
			// Check that the file is valid.
			if (!inFile.is_open()) {
				std::cout << "invalid file\n";
				break;
			}
			
			// Read the entire data from the file to the buffer.
			buffer << inFile.rdbuf();
			// Close the file.
			inFile.close();
			
			// Send the second file to the server.
			tcpClient.sendPacket(buffer.str());
			// Clear the buffer.
			buffer.str(std::string());
			// Receive the "upload done" message from the server.
			std::cout << tcpClient.recvPacket().toString();
			
			break;
		}
		case 2:
			optionAlgorithmSettings(tcpClient);
			break;
		case 3:
			tcpClient.sendPacket(input);
			std::cout << tcpClient.recvPacket().toString();
			break;
		case 4: {
			tcpClient.sendPacket(input);
			std::cout << tcpClient.recvPacket().toString();
			break;
		}
		case 5: {
			std::string path;
			std::getline(std::cin, path);
			
			std::ofstream out;
			out.open(path);
			if (!out.is_open()) {
				std::cout << "Failed loading the file " << path << std::endl;
				break;
			}
			
			tcpClient.sendPacket(input);
			
			input = tcpClient.recvPacket().toString();
			if (input != DownloadResultsCommand::START_FILE_WRITER_SYMBOL) {
				std::cout << input;
				out.close();
				break;
			}
			
			Socket::Packet packet = tcpClient.recvPacket();
			out << packet.toString();
			out.close();
			
			break;
		}
		case 8:
			keepSending = false;
			break;
		default:
			std::cout << "wrong input.\n";
		}
	}
	
	// When all's said and done, close the connection.
	tcpClient.closeSocket();
	
	return 0;
}
