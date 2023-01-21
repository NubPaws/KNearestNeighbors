#ifndef _DISPLAY_RESULTS_COMMAND
#define _DISPLAY_RESULTS_COMMAND

#include <string>

#include "Command.h"
#include "VectorDataSet.h"

class DisplayResultsCommand : public Command {
private:
	const VectorDataSet& dataset;
public:
	/**
	 * @brief Construct a new Display Results Command object.
	 * This object is used to display the results of the classification
	 * to the input.
	 * 
	 * @param io The input to display the results to.
	 * @param dataset The dataset which contains the results.
	 */
	DisplayResultsCommand(DefaultIO* io, const VectorDataSet& dataset);
	
	void execute() override;
};

#endif // _DISPLAY_RESULTS_COMMAND
