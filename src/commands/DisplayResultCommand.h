#ifndef _DISPLAY_RESULT_COMMAND
#define _DISPLAY_RESULT_COMMAND

#include "Command.h"
#include "VectorDataSet.h"

class DisplayResultCommand : public Command {
private:
	const VectorDataSet& dataset;
public:
	DisplayResultCommand(DefaultIO& io, const VectorDataSet& dataset);
	
	void execute() override;
};

#endif // _DISPLAY_RESULT_COMMAND
