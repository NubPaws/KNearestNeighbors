#include "UploadFileCommand.h"

UploadFileCommand::UploadFileCommand(DefaultIO* io, VectorDataSet& train, VectorDataSet& test)
	: Command("Upload the train file and the test file to the server.", io),
		train(train), test(test) {
	
}

void UploadFileCommand::execute() {
	
}
