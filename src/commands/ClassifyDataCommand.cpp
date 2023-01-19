#include "ClassifyDataCommand.h"

ClassifyData::ClassifyData(DefaultIO* io, KNearestNeighbors& knn, VectorDataSet& train)
	: Command("Classifies the vector data set.", io), knn(knn), train(train) {
	
}

void ClassifyData::execute() {
	if (knn.isValidDataSet()) {
		io->write("please upload data");
		return;
	}
	
	for (size_t i = 0; i < train.size(); i++) {
		train.setEntryType(i, knn.find(train[i].first));
	}
	
	io->write("classifying data complete\n");
}
