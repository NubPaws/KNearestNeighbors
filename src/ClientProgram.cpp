#include <iostream>
#include <vector>
#include <string>
#include <sstream>

#include "CommandLineArguments.h"
#include "Types.h"
#include "TCPSocket.h"
#include "VectorDistance.h"
#include "StringValidator.h"

typedef std::vector<byte> Packet;

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

static bool isInputValid(std::vector<std::string> line) {
	switch (line.size()) {
	case 1:
		return line[0] == "-1";
	case 0:
	case 2:
		return false;
	}
	
	if (!StringValidator::isInt(line[line.size() - 1]))
		return false;
	
	using VectorDistance::Calculator;
	
	if (Calculator::getType(line[line.size() - 2]) == Calculator::Type::Empty)
		return false;
	
	for (int i = 0; i < line.size() - 2; i++)
		if (!StringValidator::isDouble(line[i]))
			return false;
	
	return true;
}

static Vector strToDoubleVec(std::vector<std::string> line) {
	Vector vec;
	
	for (const std::string& str : line)
		vec.push_back(std::stod(str));
	
	return vec;
}

static Packet generatePacket(std::vector<std::string> line) {
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
	
	vec = strToDoubleVec(line);
	
	Packet packet;
	
	std::ostringstream out;
	for (const std::string& str : line)
		out << str << " ";
	
	out << (size_t)type << " " << k;
	
	std::string serializedData = out.str();
	for (size_t i = 0; i < serializedData.length(); i++)
		packet.push_back(serializedData[i]);
	
	return packet;
}

int main(int argc, const char *argv[]) {
	CommandLineArguments args(argc, argv);
	
	const size_t ipIndex = 1;
	const size_t portIndex = 2;
	
	if (args.size() < 3 || !args.isInt(portIndex)) {
		std::cout << "Invalid use of the command.\n"
			<< "Usage: " << args[0] << " [ip] [port]" << std::endl;
		return 0;
	}
	
	std::string ip = args[ipIndex];
	const int port = args.getInt(portIndex);
	
	TCPClient tcpClient(port, ip);
	tcpClient.initSocket();
	tcpClient.connectToServer();
	
	bool keepSending = true;
	std::vector<std::string> line;
	
	while (keepSending) {
		line = readLineAsVector();
		if (!isInputValid(line)) {
			std::cout << "invalid input" << std::endl;
			continue;
		}
		if (line.size() == 1 && line[0] == "-1")
			break;
		
		Packet packet = generatePacket(line);
		tcpClient.sendData(packet);
		
		std::pair<Packet, Status> result = tcpClient.receiveData();
		if (result.second == Status::Success && result.first.size() == 0) {
			std::cout << "The connection to the server was closed!" << std::endl;
			keepSending = false;
			continue;
		}
		
		if (result.second == Status::Failed) {
			std::cerr << "Failed to receive data from the server." << std::endl;
			continue;
		}
		
		packet = result.first;
		
		for (const byte& b : packet)
			std::cout << b;
		std::cout << std::endl;
	}
	
	tcpClient.closeSocket();
	
	return 0;
}
