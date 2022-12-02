#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cstddef>

#include "VectorDistanceCalculator.h"
#include "VectorDataSet.h"
#include "CommandLineArguments.h"
#include "StringValidator.h"

/**
 * @brief Reads the vector from the user.
 * 
 * @return std::vector<double> The vector the user entered or an empty vector if the input was invalid.
 */
std::vector<double> readVector() {
	std::vector<double> v;
	
	// Make a string to store the line.
	std::string line = "";
	// Read the entire line from the user.
	std::getline(std::cin, line);
	// Convert the line into a string stream.
	std::istringstream iss(line);
	
	/*
	While there is still some data to read, 
	read it as a double, Each double is then pushed back into the vector we have.
	*/
	std::string str;
	while (iss >> str) {
		if (StringValidator::isDouble(str)) {
			v.push_back(std::stod(str));
		} else {
			v.clear();
			return v;
		}
	}
	
	// Return the vector.
	return v;
}

int main(int argc, const char* argv[]) {
	CommandLineArguments args(argc, argv);
	
	const std::size_t kIndex = 1, filenameIndex = 2, algorithmType = 3;
	// Check command line input.
	if (args.size() < 4 || !args.isInt(kIndex))
		return 0;
	
	int k = args.getInt(kIndex);
	std::string filename = args.getStr(filenameIndex);
	auto distanceAlg = VectorCalculation::DistanceCalculator::getCalculator(args.getStr(algorithmType));
	
	return 0;
}
