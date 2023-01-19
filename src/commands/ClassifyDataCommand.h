#ifndef _CLASSIFY_DATA_COMMAND
#define _CLASSIFY_DATA_COMMAND

#include "Command.h"
#include "KNearestNeighbors.h"
#include "VectorDataSet.h"

class ClassifyData : public Command {
private:
	KNearestNeighbors& knn;
	VectorDataSet& train;
public:
	/**
	 * @brief Construct a new Classify Data object.
	 * 
	 * @param io The input for the command.
	 * @param knn The KNN algorithm
	 * @param train The dataset uploaded from the user, to be classified.
	 */
	ClassifyData(DefaultIO* io, KNearestNeighbors& knn, VectorDataSet& train);
	
	void execute() override;
};

#endif // _CLASSIFY_DATA_COMMAND
