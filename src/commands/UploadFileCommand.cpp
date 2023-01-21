#include "UploadFileCommand.h"

#include <string>
#include <sstream>

UploadFileCommand::UploadFileCommand(DefaultIO* io, KNearestNeighbors& knn, VectorDataSet& train, VectorDataSet& test)
	: Command("Upload the train file and the test file to the server.", io),
		train(train), test(test), knn(knn) {
	
}

void UploadFileCommand::execute() {
	std::string input;
		
	io->write("Please upload your local train CSV file.\n");
	input = io->read();
	if (input == Command::ERROR_SYMBOL) {
		clearDataSets();
		return;
	}
	
	if (!train.set(input, true)) {
		io->write(Command::ERROR_SYMBOL);
		io->write("Error parsing the data\n");
		clearDataSets();
		return;
	}
	
	io->write("Upload complete.\n");
	
	io->write("Please upload your local test CSV file.\n");
	input = io->read();
	if (input == Command::ERROR_SYMBOL) {
		clearDataSets();
		return;
	}
	
	if (test.set(input, false)) {
		io->write(Command::ERROR_SYMBOL);
		io->write("Error parsing the data\n");
		clearDataSets();
		return;
	}
	
	io->write("Upload complete.\n");
	
	knn.setDataSet(train);
}

void UploadFileCommand::clearDataSets() {
	train.clear();
	test.clear();
}
