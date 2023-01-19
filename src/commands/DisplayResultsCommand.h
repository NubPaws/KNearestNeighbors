#ifndef _DISPLAY_RESULTS_COMMAND
#define _DISPLAY_RESULTS_COMMAND

#include "Command.h"
#include "VectorDataSet.h"

class DisplayResultsCommand : public Command {
private:
	const VectorDataSet& dataset;
public:
	DisplayResultsCommand(DefaultIO& io, const VectorDataSet& dataset);
	
	void execute() override;
};

#endif // _DISPLAY_RESULTS_COMMAND
