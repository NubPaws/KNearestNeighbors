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
	DownloadResultsCommand(DefaultIO* io, const VectorDataSet& dataset);
	
	void execute() override;
};

#endif // _DOWNLOAD_RESULTS_COMMAND
