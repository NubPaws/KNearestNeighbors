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
	/**
	 * @brief Construct a new Upload File Command object.
	 * This object handles communicating with the user to what
	 * data to upload. It also validates it on the server side.
	 * 
	 * @param io The io to read and write from the data.
	 * @param knn The KNN algoritm to set with the classifcation.
	 * @param train The train data.
	 * @param test The data to test on.
	 */
	UploadFileCommand(DefaultIO* io, KNearestNeighbors& knn, VectorDataSet& train, VectorDataSet& test);
	
	void execute() override;
private:
	/**
	 * @brief Helpfer function to clear both the train and the test
	 * vector data sets.
	 */
	void clearDataSets();
};

#endif // _UPLOAD_FILE_COMMAND_H
