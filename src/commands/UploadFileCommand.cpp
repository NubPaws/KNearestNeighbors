#include "UploadFileCommand.h"

#include <string>
#include <sstream>

UploadFileCommand::UploadFileCommand(DefaultIO* io, KNearestNeighbors& knn, VectorDataSet& train, VectorDataSet& test)
	: Command("Upload the train file and the test file to the server.", io),
		train(train), test(test), knn(knn) {
	
}

void UploadFileCommand::execute() {
	std::stringstream ss;
	
	io->write("Please upload your local train CSV file.\n");
	ss << io->read();
	if (ss.str() == "")
		return;
	
	train.set(ss, true);
	ss.str(std::string());
	
	io->write("Upload complete.\n");
	
	io->write("Please upload your local test CSV file.\n");
	ss << io->read();
	if (ss.str() == "")
		return;
	
	test.set(ss, false);
	ss.str(std::string());
	
	io->write("Upload complete.\n");
	
	knn.setDataSet(train);
}
