#include "DownloadResultsCommand.h"

#include <sstream>

const std::string DownloadResultsCommand::START_FILE_WRITER_SYMBOL = "/-\\";

DownloadResultsCommand::DownloadResultsCommand(DefaultIO& io, const VectorDataSet& dataset)
	: Command("Downloads the results of the classification.", io), dataset(dataset) {
	
}

void DownloadResultsCommand::execute() {
	if (dataset.size() == 0) {
		io.write("please upload data\n");
		return;
	}
	if (dataset[0].second == "") {
		io.write("please classify the data\n");
		return;
	}
	
	io.write(START_FILE_WRITER_SYMBOL);
	
	std::stringstream ss;
	for (size_t i = 0; i < dataset.size(); i++) {
		ss << i + 1 << "\t" << dataset[i].second << "\n";
		io.write(ss.str());
		ss.clear();
	}
	io.write("Done.\n");
}
