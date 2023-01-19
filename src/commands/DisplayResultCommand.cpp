#include "DisplayResultCommand.h"

#include <sstream>

DisplayResultCommand::DisplayResultCommand(DefaultIO& io, const VectorDataSet& dataset)
	: Command("Displays the results of the classification.", io), dataset(dataset) {
	
}

void DisplayResultCommand::execute() {
	if (dataset.size() == 0) {
		io.write("please upload data\n");
		return;
	}
	if (dataset[0].second == "") {
		io.write("please classify the data\n");
		return;
	}
	
	std::stringstream ss;
	for (size_t i = 0; i < dataset.size(); i++) {
		ss << i + 1 << "\t" << dataset[i].second << "\n";
		io.write(ss.str());
		ss.clear();
	}
	io.write("Done.\n");
}
