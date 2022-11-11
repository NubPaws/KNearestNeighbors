#include <iostream>
#include <iomanip>
#include "Vector.h"
#include "VectorDistanceCalculator.h"

bool isWhole(double n) {
	return n - (long)n == 0;
}

int main() {
	// Create the variables to read to.
	double x, y, z;
	
	// Read the first vector.
	std::cin >> x >> y >> z;
	Vector v1(x, y, z);
	
	// Read the second vector.
	std::cin >> x >> y >> z;
	Vector v2(x, y, z);
	
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
