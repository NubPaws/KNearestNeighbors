#include <iostream>
#include "Vector.h"
#include "VectorDistanceCalculator.h"

int main() {
	
	double x, y, z;
	
	std::cin >> x >> y >> z;
	Vector v1(x, y, z);
	
	std::cin >> x >> y >> z;
	Vector v2(x, y, z);
	
	std::cout << VectorDistanceCalculator::euclidean(v1, v2) << std::endl
			<< VectorDistanceCalculator::manhattan(v1, v2) << std::endl
			<< VectorDistanceCalculator::chebyshev(v1, v2) << std::endl
			<< VectorDistanceCalculator::canberra(v1, v2) << std::endl
			<< VectorDistanceCalculator::minkowski(v1, v2, 1) << std::endl;
	
	return 0;
}
