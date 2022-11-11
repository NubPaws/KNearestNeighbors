#include <iostream>
#include <iomanip>
#include "Vector.h"
#include "VectorDistanceCalculator.h"

int main() {
	double x, y, z;
	
	std::cin >> x >> y >> z;
	Vector v1(x, y, z);
	
	std::cin >> x >> y >> z;
	Vector v2(x, y, z);
	
	double distances[5] = {
		VectorDistanceCalculator::euclidean(v1, v2),
		VectorDistanceCalculator::manhattan(v1, v2),
		VectorDistanceCalculator::chebyshev(v1, v2),
		VectorDistanceCalculator::canberra(v1, v2),
		VectorDistanceCalculator::minkowski(v1, v2, 2)
	};
	
	std::cout << std::setprecision(16);
	for (int i = 0; i < 5; i++) {
		if (i > 0)
			std::cout << std::endl;
		std::cout << distances[i];
		if (distances[i] - (long)distances[i] == 0)
			std::cout << ".0";
	}
	
	return 0;
}
