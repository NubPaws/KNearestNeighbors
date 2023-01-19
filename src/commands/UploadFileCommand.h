#ifndef _UPLOAD_FILE_COMMAND_H
#define _UPLOAD_FILE_COMMAND_H

#include "Command.h"
#include "VectorDataSet.h"

class UploadFileCommand : public Command {
private:
	VectorDataSet& train;
	VectorDataSet& test;
public:
	UploadFileCommand(DefaultIO* io, VectorDataSet& train, VectorDataSet& test);
	
	void execute() override;
};

#endif // _UPLOAD_FILE_COMMAND_H
