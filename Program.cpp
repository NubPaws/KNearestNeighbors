#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <sstream>
#include <cstdlib>
#include "VectorDistanceCalculator.h"

/**
 * @brief Checks if a string can be converted to a double.
 * 
 * @param str The string to check against.
 * @return true If the string can be converted to a double.
 * @return false If the string cannot be converted to a double.
 */
bool isNumber(const std::string& str) {
	if (str.length() == 0)
		return false;
	
	// Flags to check if the number is a negative and if it has a decimal point.
	bool isNegative = str[0] == '-';
	bool hasDecimal = false;
	
	/*
	Start the loop from the 0th index if the number is not a negative number. Otherwise
	start it from the 1st index. For each index check if the string only contains numbers
	and 1 decimal point. If not return out a false value.
	*/
	for (int i = isNegative; i < str.length(); i++) {
		if ((str[i] < '0' || '9' < str[i]) && str[i] != '.')
			return false;
		
		if (str[i] == '.') {
			if (hasDecimal)
				return false;
			hasDecimal = true;
		}
	}
	
	// If the string only contains a - and a . then return false, otherwise it is a valid string
	// and we can return true.
	return str.length() != (isNegative + hasDecimal);
}

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
		if (isNumber(str)) {
			v.push_back(std::atof(str.c_str()));
		} else {
			v.clear();
			return v;
		}
	}
	
	// Return the vector.
	return v;
}

bool isWhole(const double n) {
	return n - (long)n == 0;
}

int main() {
	// Create the vectors and read the data into them.
	std::vector<double> v1 = readVector();
	std::vector<double> v2 = readVector();
	
	if (v1.size() != v2.size() || v1.size() == 0 || v2.size() == 0) {
		std::cout << "Please enter two valid vectors" 
		"- both vectors must contain only numbers and be of the same length." << std::endl;
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
