#include <sstream>

#include "AlgorithmSettingsCommand.h"
#include "StringUtils.h"

AlgorithmSettingsCommand::AlgorithmSettingsCommand(DefaultIO* io, KNearestNeighbors& knn)
	: Command("Sets the settings of the KNN algorithm.", io), knn(knn) {
	
}

void AlgorithmSettingsCommand::execute() {
	std::stringstream ss;
	
	ss << "The current KNN parameters are: K = "
		<< knn.getK()
		<< ", distance metric = "
		<< knn.getMetric()
		<< "\n";
	io->write(ss.str());
	
	std::string in = io->read();
	if (in.size() == 0)
		return;
	
	std::vector<std::string> user = Utils::readLineAsVector(in);
	
	if (!Utils::isInt(user[0])) {
		io->write("Invalid value for K\n");
		return;
	}
	
	int k = std::stoi(user[0]);
	if (k <= 0) {
		io->write("Invalid value for K\n");
		return;
	}
	
	using Calc = VectorDistance::Calculator;
	
	Calc::Type type = Calc::getType(user[1]);
	if (type == Calc::Type::Empty) {
		io->write("Invalid value for metric\n");
		return;
	}
	knn.setDistanceType(type);
	knn.setK(k);
}