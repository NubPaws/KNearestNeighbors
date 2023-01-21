#ifndef _DOWNLOAD_RESULTS_COMMAND
#define _DOWNLOAD_RESULTS_COMMAND

#include <string>

#include "Command.h"
#include "VectorDataSet.h"

class DownloadResultsCommand : public Command {
public:
	static const std::string START_FILE_WRITER_SYMBOL;
private:
	const VectorDataSet& dataset;
public:
	/**
	 * @brief Construct a new Download Results Command object.
	 * This object downloads the results from the given dataset
	 * into the io. The user is incharge of actually writing them.
	 * 
	 * @param io The io to send the data over.
	 * @param dataset The dataset from which to get the data.
	 */
	DownloadResultsCommand(DefaultIO* io, const VectorDataSet& dataset);
	
	void execute() override;
};

#endif // _DOWNLOAD_RESULTS_COMMAND
