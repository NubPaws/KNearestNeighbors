#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cstddef>

#include "KNearestNeighbors.h"
#include "VectorDistance.h"
#include "VectorDataSet.h"
#include "CommandLineArguments.h"
#include "StringValidator.h"

/**
 * @brief Reads the vector from the user.
 * 
 * @return std::vector<double> The vector the user entered or an empty vector if the input was invalid.
 */
std::vector<double> readVector(std::istream& input) {
	std::vector<double> v;
	
	// Make a string to store the line.
	std::string line = "";
	// Read the entire line from the user.
	std::getline(input, line);
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
	
	const std::size_t kIndex = 1, filenameIndex = 2, algorithmIndex = 3;
	// Check command line input.
	if (args.size() < 4 || !args.isInt(kIndex)) {
		std::cout << "Please enter command line arguments." << std::endl;
		return 0;
	}
	
	int k = args.getInt(kIndex);
	std::string filename = args.getStr(filenameIndex);
	auto distanceAlg = VectorDistance::Calculator::getType(args.getStr(algorithmIndex));
	
	if (distanceAlg == VectorDistance::Calculator::Type::Empty) {
		std::cout << "Please choose a valid distance algorithm." << std::endl;
		return 0;
	}
	
	VectorDataSet vds(filename);
	KNearestNeighbors knn(vds, distanceAlg);
	std::vector<double> vec = readVector(std::cin);
	
	if (vec.size() != vds.width()) {
		std::cout << "Make sure to enter a vector of the correct size." << std::endl;
		return 0;
	}
	
	std::string result = knn.find(vec, args.getInt(kIndex));
	
	std::cout << result << std::endl;
	
	return 0;
}
