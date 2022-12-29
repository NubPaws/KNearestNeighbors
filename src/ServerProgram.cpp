#include <iostream>
#include <string>
#include <sstream>
#include <utility>
#include <vector>

#include "TCPSocket.h"
#include "Types.h"
#include "CommandLineArguments.h"
#include "VectorDistance.h"
#include "VectorDataSet.h"
#include "KNearestNeighbors.h"

static std::vector<std::string> packetToData(Packet packet) {
	std::vector<std::string> data;
	
	std::istringstream iss(std::string(packet.begin(), packet.end()));
	
	std::string str;
	while (iss >> str) {
		data.push_back(str);
	}
	
	return data;
}

Packet serializeString(std::string str) {
	Packet data;
	
	for (size_t i = 0; i < str.length(); i++)
		data.push_back(str[i]);
	
	return data;
}

int main(int argc, char const *argv[]) {
	CommandLineArguments args(argc, argv);
	
	const size_t fileIndex = 1;
	const size_t portIndex = 2;
	
	if (args.size() < 2 || !args.isInt(portIndex)) {
		std::cout << "Invalid use of the command.\n"
			<< "Usage: " << args[0] << " [file] [port]" << std::endl;
		return 0;
	}
	
	// Setting up server
	TCPServer tcpServer(args.getInt(portIndex), "127.0.0.1", 5);
	
	tcpServer.initSocket();
	tcpServer.bindSocket();
	tcpServer.listenForConnections();
	
	using VectorDistance::Calculator;
	
	VectorDataSet vds(args[fileIndex]);
	KNearestNeighbors knn(vds, Calculator::Type::Empty);
	
	int clientSocket = tcpServer.acceptConnection();
	while (clientSocket != -1) {
		std::pair<Packet, Status> result = tcpServer.receiveData(clientSocket);
		while (result.second != Status::Success || result.first.size() != 0) {
			if (result.second == Status::Failed) {
				std::cerr << "Failed to receive data from the client." << std::endl;
				continue;
			}
			
			std::vector<std::string> data = packetToData(result.first);
			
			int k = std::stoi(data[data.size() - 1]);
			data.pop_back();
			
			knn.setDistanceType((Calculator::Type)std::stoi(data[data.size() - 1]));
			data.pop_back();
			
			Vector vec;
			for (const std::string& str : data)
				vec.push_back(std::stod(str));
			data.clear();
			
			if (vec.size() != vds.width() || vec.size() == 0) {
			
			std::string vectorClass = knn.find(vec, k);
			
			tcpServer.sendData(clientSocket, serializeString(vectorClass));
			
			result = tcpServer.receiveData(clientSocket);
		}
		
		tcpServer.closeClientConnection(clientSocket);
		clientSocket = tcpServer.acceptConnection();
	}
	
	tcpServer.closeSocket();
	
	return 0;
}
