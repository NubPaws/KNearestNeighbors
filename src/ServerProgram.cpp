#include <iostream>
#include <string>
#include <sstream>
#include <utility>
#include <vector>

#include "Socket.h"
#include "Types.h"
#include "CommandLineArguments.h"
#include "VectorDistance.h"
#include "VectorDataSet.h"
#include "KNearestNeighbors.h"
#include "Packet.h"

using Socket::TCPServer;

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
	
	// Set up the KNN algorithm and load the file.
	VectorDataSet vds(args[fileIndex]);
	KNearestNeighbors knn(vds, Calculator::Type::Empty);
	
	// Start accepting connections.
	int clientSocket = tcpServer.acceptConnection();
	while (clientSocket != -1) {
		Socket::Packet packet = tcpServer.receiveData(clientSocket);
		
		/**
		 * Iterate over the open connections. Keep reading from the same connection
		 * as long as we are getting a valid packet with a size not equal to zero.
		 * If either of those cases are false then we know that the connection
		 * either closed or some other error has occured.
		*/
		while (packet.isValid() && packet.size() != 0) {
			std::vector<std::string> data = packet.toVector();
			
			int k = std::stoi(data[data.size() - 1]);
			data.pop_back();
			
			// Prepare the distance algorithm.
			knn.setDistanceType((Calculator::Type)std::stoi(data[data.size() - 1]));
			data.pop_back();
			
			// Load the vector to match against.
			Vector vec;
			for (const std::string& str : data)
				vec.push_back(std::stod(str));
			data.clear();
			
			// As long as the vector is valid.
			if (vec.size() != vds.width() || vec.size() == 0) {
				tcpServer.sendData(clientSocket, Socket::Packet("invalid input"));
				continue;
			}
			
			// Calculate the KNN.
			std::string vectorClass = knn.find(vec, k);
			
			// Tell the user.
			tcpServer.sendData(clientSocket, Socket::Packet(vectorClass));
			
			// Read the next vector.
			packet = tcpServer.receiveData(clientSocket);
		}
		
		if (!packet.isValid())
			std::cerr << "Failed to receive data from the client." << std::endl;
		
		// Close the current connection and open up another one.
		tcpServer.closeClientConnection(clientSocket);
		clientSocket = tcpServer.acceptConnection();
	}
	
	// Close the server.
	tcpServer.closeSocket();
	
	return 0;
}
