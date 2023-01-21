#ifndef _UPLOAD_FILE_COMMAND_H
#define _UPLOAD_FILE_COMMAND_H

#include "Command.h"
#include "VectorDataSet.h"
#include "KNearestNeighbors.h"

class UploadFileCommand : public Command {
private:
	KNearestNeighbors& knn;
	VectorDataSet& train;
	VectorDataSet& test;
public:
	UploadFileCommand(DefaultIO* io, KNearestNeighbors& knn, VectorDataSet& train, VectorDataSet& test);
	
	void execute() override;
private:
	void clearDataSets();
};

#endif // _UPLOAD_FILE_COMMAND_H
