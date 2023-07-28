#include <iostream>
#include <string>
#include <utility>

#include "Socket.h"
#include "Types.h"
#include "CommandLineArguments.h"
#include "Packet.h"
#include "SocketIO.h"
#include "CommandLineInterface.h"
#include "ThreadPool.h"

using namespace Socket;

void handleClient(TCPSocket socket) {
	DefaultIO *clientIO = new SocketIO(socket);
	
	CLI cli(clientIO);
	
	cli.start();
	
	// Close the current connection and open up another one.
	delete clientIO;
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
	
	// Create the thread pool.
	ThreadPool<TCPSocket> threadPool(5);
	// Start the thread pool.
	threadPool.start();
	
	// Start accepting connections.
	TCPSocket clientSocket = tcpServer.acceptConnection();
	while (clientSocket.isValidSocket()) {
		// Queue the next connection.
		threadPool.queue(handleClient, clientSocket);
		// Wait for the next connection.
		clientSocket = tcpServer.acceptConnection();
	}
	
	// Terminate the threads.
	threadPool.stop();
	
	// Close the server.
	tcpServer.closeSocket();
	
	return 0;
}
