#include "VectorDistanceCalculator.h"
#include "Vector.h"
#include <cmath>

double VectorDistanceCalculator::euclidean(const Vector v1, const Vector v2) {
	//euclidean distance is a specific case of minowski equation,in order to save code we just use it
	return VectorDistanceCalculator::minkowski(v1, v2, 2);
}

double VectorDistanceCalculator::manhattan(const Vector v1, const Vector v2) {
	//manhatan equation is a specific case of minowski equation,in order to save code we just use it
	return minkowski(v1, v2, 1);
}

double VectorDistanceCalculator::chebyshev(const Vector v1, const Vector v2) {
	
	double dist = 0;
	for (int i = 0; i < 3; i++) {
		double tmp = std::abs(v1[i] - v2[i]);
		if (tmp > dist)
			dist = tmp;
	}
	
	return dist;
}

double VectorDistanceCalculator::canberra(const Vector v1, const Vector v2) {
	// The case where both coordinates are 0 is defined as 0/0 = 0
	double canberraSum = 0;
	
	for (int i = 0; i < 3; i++)
		if (!(v1[i] == 0 && v2[i] == 0))
			canberraSum += std::abs(v1[i] - v2[i]) / (std::abs(v1[i]) + std::abs(v2[i]));
	
	return canberraSum;
}

double VectorDistanceCalculator::minkowski(const Vector v1, const Vector v2, const int p) {
	double distance = 0;
	for (int i = 0; i < 3; i++) {
		distance += std::pow(std::abs(v1[i] - v2[i]), p);
	}
	
	return pow(distance, 1.0 / p);
}
