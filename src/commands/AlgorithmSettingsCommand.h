#ifndef _ALGORITHM_SETTINGS_COMMAND_H
#define _ALGORITHM_SETTINGS_COMMAND_H

#include "Command.h"
#include "KNearestNeighbors.h"

class AlgorithmSettingsCommand : public Command {
private:
	KNearestNeighbors &knn;
public:
	AlgorithmSettingsCommand(KNearestNeighbors &knn, DefaultIO &io);
	void execute() override;
};

#endif // _ALGORITHM_SETTINGS_COMMAND_H
