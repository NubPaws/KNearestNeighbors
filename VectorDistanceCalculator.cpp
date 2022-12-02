#include "VectorDistanceCalculator.h"
#include <vector>
#include <cmath>

double VectorCalculation::euclidean(const std::vector<double>& v1, const std::vector<double>& v2) {
	//euclidean distance is a specific case of minowski equation,in order to save code we just use it
	return VectorCalculation::minkowski(v1, v2, 2);
}

double VectorCalculation::manhattan(const std::vector<double>& v1, const std::vector<double>& v2) {
	//manhatan equation is a specific case of minowski equation,in order to save code we just use it
	return VectorCalculation::minkowski(v1, v2, 1);
}

double VectorCalculation::chebyshev(const std::vector<double>& v1, const std::vector<double>& v2) {
	
	double dist = 0;
	const unsigned int len = v1.size() >= v2.size() ? v2.size() : v1.size();
	for (int i = 0; i < len; i++) {
		double tmp = std::abs(v1[i] - v2[i]);
		if (tmp > dist)
			dist = tmp;
	}
	
	return dist;
}

double VectorCalculation::canberra(const std::vector<double>& v1, const std::vector<double>& v2) {
	// The case where both coordinates are 0 is defined as 0/0 = 0
	double canberraSum = 0;
	
	const unsigned int len = v1.size() >= v2.size() ? v2.size() : v1.size();
	for (int i = 0; i < len; i++)
		if (!(v1[i] == 0 && v2[i] == 0))
			canberraSum += std::abs(v1[i] - v2[i]) / (std::abs(v1[i]) + std::abs(v2[i]));
	
	return canberraSum;
}

double VectorCalculation::minkowski(const std::vector<double>& v1, const std::vector<double>& v2, const int p) {
	double distance = 0;
	const unsigned int len = v1.size() >= v2.size() ? v2.size() : v1.size();
	for (int i = 0; i < len; i++) {
		distance += std::pow(std::abs(v1[i] - v2[i]), p);
	}
	
	return pow(distance, 1.0 / p);
}
