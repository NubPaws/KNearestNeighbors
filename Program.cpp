#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <sstream>
#include "VectorDistanceCalculator.h"

std::vector<double> readVector() {
	std::vector<double> v;
	
	// Make a string to store the line.
	std::string line = "";
	// Read the entire line from the user.
	std::getline(std::cin, line);
	// Convert the line into a string stream.
	std::istringstream iss(line);
	
	/*
	While there is still some data to read, read it as a double. Each double is them
	pushed back into the vector we have.
	*/
	double num;
	while (iss >> num)
		v.push_back(num);
	
	// Return the vector.
	return v;
}

bool isWhole(double n) {
	return n - (long)n == 0;
}

int main() {
	// Create the vectors and read the data into them.
	std::vector<double> v1 = readVector();
	std::vector<double> v2 = readVector();
	
	if (v1.size() != v2.size()) {
		std::cout << "Please enter two vectors of the size." << std::endl;
		return 0;
	}
	
	// Calculate the distances.
	const int distanceCount = 5;
	double distances[distanceCount] = {
		VectorDistanceCalculator::euclidean(v1, v2),
		VectorDistanceCalculator::manhattan(v1, v2),
		VectorDistanceCalculator::chebyshev(v1, v2),
		VectorDistanceCalculator::canberra(v1, v2),
		VectorDistanceCalculator::minkowski(v1, v2, 2)
	};
	
	// Set the precision to the full double precision - 16 digits.
	std::cout << std::setprecision(16);
	/*
	For each distance print out the distance. If the number is a whole number we'll
	manually add a ".0" after it. Otherwise, just let it print the regular way.
	Make sure to add a new line for each of our distances excluding the first.
	*/
	for (int i = 0; i < distanceCount; i++) {
		if (i > 0)
			std::cout << std::endl;
		
		std::cout << distances[i];
		
		if (isWhole(distances[i]))
			std::cout << ".0";
	}
	
	return 0;
}
