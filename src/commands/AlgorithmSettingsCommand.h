#ifndef _ALGORITHM_SETTINGS_COMMAND_H
#define _ALGORITHM_SETTINGS_COMMAND_H

#include "Command.h"
#include "KNearestNeighbors.h"

class AlgorithmSettingsCommand : public Command {
private:
	KNearestNeighbors &knn;
public:
	/**
	 * @brief Construct a new Algorithm Settings Command object
	 * 
	 * @param io The io to write and read from.
	 * @param knn The KNN class to change the settings to.
	 */
	AlgorithmSettingsCommand(DefaultIO* io, KNearestNeighbors& knn);
	void execute() override;
};

#endif // _ALGORITHM_SETTINGS_COMMAND_H
