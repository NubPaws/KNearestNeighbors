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
#include "DefaultIO.h"
#include "StringUtils.h"
#include "CommandClasses.h"

using Socket::TCPServer;

std::string getWelcomeScreenMessage() {
	return "Welcome to the KNN Classifier Server. Please choose an option:\n"
		"1. upload an unclassified csv data file\n"
		"2. algorithm settings\n"
		"3. classify data\n"
		"4. display results\n"
		"5. download results\n"
		"8. exit\n";
}

void handleClient(Socket::TCPSocket socket) {
	DefaultIO *clientIO = new SocketIO(socket);
	
	VectorDataSet train = VectorDataSet("./datasets/iris/iris_Unclassified.csv", false);
	VectorDataSet tmp("./datasets/iris/iris_classified.csv");
	KNearestNeighbors knn(tmp, VectorDistance::Calculator::Type::Euclidean, 5);
	
	clientIO->write(getWelcomeScreenMessage());
	
	std::string clientInput;
	int option = 0;
	
	do {
		clientInput = clientIO->read();
		
		if (clientInput == "") {
			clientIO->write("invalid packet\n");
			continue;
		}
		
		if (!Utils::isInt(clientInput)) {
			clientIO->write("invalid input\n");
			continue;
		}
		
		option = std::stoi(clientInput);
		
		switch (option) {
		case 1:
			break;
		case 2: {
			AlgorithmSettingsCommand asc(clientIO, knn);
			asc.execute();
			break;
		}
		case 3: {
			ClassifyDataCommand cdc(clientIO, knn, train);
			cdc.execute();
			break;
		}
		case 4: {
			DisplayResultsCommand drc(clientIO, train);
			drc.execute();
			break;
		}
		case 5:
			break;
		case 8:
			break;
		default:
			clientIO->write("invalid input\n");
		}
		
	} while (option != 8);
	
	// Close the current connection and open up another one.
	socket.closeSocket();
}

int main(int argc, char const *argv[]) {
	CommandLineArguments args(argc, argv);
	
	const size_t portIndex = 1;
	
	if (args.size() < 1 || !args.isInt(portIndex)) {
		std::cout << "Invalid use of the command.\n"
			<< "Usage: " << args[0] << " [port]" << std::endl;
		return 0;
	}
	
	// Setting up server
	TCPServer tcpServer(args.getInt(portIndex), "127.0.0.1", 5);
	try {
		
		tcpServer.bindSocket();
		tcpServer.listenForConnections();
	}
	catch (std::exception exception){
		std::cerr << exception.what() << std::endl;
		// error in creating server socket means that there are no socket resources to free
		return -1;
	}
	
	using VectorDistance::Calculator;
	
	// Start accepting connections.
	TCPSocket clientSocket = tcpServer.acceptConnection();
	while (clientSocket.isValidSocket()) {
		handleClient(clientSocket);
		
		/**
		 * Iterate over the open connections. Keep reading from the same connection
		 * as long as we are getting a valid packet with a size not equal to zero.
		 * If either of those cases are false then we know that the connection
		 * either closed or some other error has occurred.
		*/
		/*while (packet.isValid() && packet.size() != 0) {
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
				clientIO.write("invalid input");
				continue;
			}
			
			// Calculate the KNN.
			std::string vectorClass = knn.find(vec);
			
			// Tell the user.
			clientIO.write(vectorClass);
			
			// Read the next vector.
			packet = clientIO.read();
		}*/
		
		
		clientSocket = tcpServer.acceptConnection();
	}
	
	// Close the server.
	tcpServer.closeSocket();
	
	return 0;
}
