#include "UploadFileCommand.h"

#include <string>
#include <sstream>

UploadFileCommand::UploadFileCommand(DefaultIO* io, VectorDataSet& train, VectorDataSet& test)
	: Command("Upload the train file and the test file to the server.", io),
		train(train), test(test) {
	
}

void UploadFileCommand::execute() {
	io->write("Please upload your local train CSV file.\n");
	
	std::stringstream ss;
	ss << io->read();
	
	train = VectorDataSet(ss, true);
	ss.str(std::string());
	
	io->write("Upload complete.\n");
	
	io->write("Please upload your local test CSV file.\n");
	
	ss << io->read();
	
	test = VectorDataSet(ss, false);
	
	io->write("Upload complete.\n");
}
