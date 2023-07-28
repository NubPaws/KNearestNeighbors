#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <thread>

#include "CommandLineArguments.h"
#include "Types.h"
#include "Socket.h"
#include "Packet.h"
#include "CommandClasses.h"
#include "StringUtils.h"
#include "CommandLineInterface.h"

using Socket::TCPClient;

std::string FAILED_SERVER_CONNECTION = "Failed to connect to server";

static bool uploadFileToServer(TCPClient& client) {
	std::string path;

	// Read the path of the file.
	std::getline(std::cin, path);

	std::ifstream inFile;
	// Open the file.
	inFile.open(path);

	// Check that the file has opened successfully.
	if (!inFile.is_open()) {
		std::cout << "invalid file\n";
		client.sendPacket(Command::ERROR_SYMBOL);
		return false;
	}

	std::stringstream buffer;
	// Read the entire file into a buffer.
	buffer << inFile.rdbuf();
	// Close the file.
	inFile.close();

	// Send the data from the file to the server.
	client.sendPacket(buffer.str());
	// Clear the buffer.
	buffer.str(std::string());
	return true;
}

void optionUploadFile(TCPClient tcpClient) {
	// Send the number to server to start the command.
	std::string path;
	std::string input;
	
	// Read the message, to upload the first file, from the server.
	std::cout << tcpClient.recvPacket().toString();

	bool isUploadSucceed = uploadFileToServer(tcpClient);
	if (!isUploadSucceed)
		return;
	
	// Print "upload complete" message
	std::cout << tcpClient.recvPacket().toString();
	
	// Print the next message to the screen (whether it is an error message or not).
	input = tcpClient.recvPacket().toString();
	// If it is an error message, stop executing.
	if (input == Command::ERROR_SYMBOL)
		return;
	
	std::cout << input;
	isUploadSucceed = uploadFileToServer(tcpClient);
	if (!isUploadSucceed)
		return;

	// Receive the string from the server.
	input = tcpClient.recvPacket().toString();
	// Print the next message to the screen (whether it is an error message or not).
	std::cout << input;
	// If it is an error message, stop executing.
	if (input == Command::ERROR_SYMBOL)
		return;
	
}

void optionAlgorithmSettings(Socket::TCPClient& client) {
	std::cout << client.recvPacket().toString();
	
	std::string line;
	std::getline(std::cin, line);
	client.sendPacket(line);
	std::cout << client.recvPacket().toString();
}

void optionDownloadFile(TCPClient& tcpClient, std::string input) {
	std::string path;
	std::getline(std::cin, path);
	
	std::ofstream out;
	out.open(path);
	if (!out.is_open()) {
		std::cout << "Failed loading the file " << path << std::endl;
		return;
	}
	out.close();
	
	tcpClient.sendPacket(input);
	
	input = tcpClient.recvPacket().toString();
	if (input != DownloadResultsCommand::START_FILE_WRITER_SYMBOL) {
		std::cout << input;
		out.close();
		return;
	}
	
	std::thread thd([path, &tcpClient] {
		std::ofstream out;
		out.open(path);
		out << tcpClient.recvPacket().toString();
		out.close();
	});
	thd.join();
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
		return 0;
	}
	
	bool printMenu = true;
	std::string input;
	CLI::Option option = CLI::Option::Empty;
	while (option != CLI::Option::Exit) {
		// Read the menu from the server.
		if (printMenu) {
			std::cout << tcpClient.recvPacket().toString();
		} else {
			printMenu = false;
		}
		
		std::getline(std::cin, input);
		
		if (!Utils::isInt(input)) {
			std::cout << "wrong input.\n";
			printMenu = false;
			continue;
		}
		
		option = (CLI::Option)std::stoi(input);
		
		switch (option) {
		case CLI::Option::Upload: {
			tcpClient.sendPacket(input);
			optionUploadFile(tcpClient);
			break;
		}
		case CLI::Option::Settings:
			tcpClient.sendPacket(input);
			optionAlgorithmSettings(tcpClient);
			break;
		case CLI::Option::Classifiy:
			tcpClient.sendPacket(input);
			std::cout << tcpClient.recvPacket().toString();
			break;
		case CLI::Option::Display:
			tcpClient.sendPacket(input);
			std::cout << tcpClient.recvPacket().toString();
			break;
		case CLI::Option::Download:
			optionDownloadFile(tcpClient, input);
			break;
		case CLI::Option::Exit:
			tcpClient.sendPacket(input);
			break;
		default:
			std::cout << "wrong input.\n";
			printMenu = false;
		}
	}
	
	// When all's said and done, close the connection.
	tcpClient.closeSocket();
	
	return 0;
}
