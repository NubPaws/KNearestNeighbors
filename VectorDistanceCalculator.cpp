#include "VectorDistanceCalculator.h"
#include <vector>
#include <cmath>

namespace VectorCalculation {
	// To make the code a bit shorter and more readable.
	using cVectorRef = const std::vector<double>&;
	
	double DistanceCalculator::operator()(cVectorRef v1, cVectorRef v2) const {
		return this->calculate(v1, v2);
	}
	
	std::unique_ptr<DistanceCalculator> DistanceCalculator::getCalculator(const std::string& name) {
		if (name == "AUC")
			return std::unique_ptr<DistanceCalculator>(new EuclideanDistanceCalculator());
		if (name == "MAN")
			return std::unique_ptr<DistanceCalculator>(new ManhattanDistanceCalculator());
		if (name == "CHB")
			return std::unique_ptr<DistanceCalculator>(new ChebyshevDistanceCalculator());
		if (name == "CAN")
			return std::unique_ptr<DistanceCalculator>(new CanberraDistanceCalculator());
		if (name == "MIN")
			return std::unique_ptr<DistanceCalculator>(new MinkowskiDistanceCalculator());
		return std::unique_ptr<DistanceCalculator>(nullptr);
	}
	
	double EuclideanDistanceCalculator::calculate(cVectorRef v1, cVectorRef v2) const {
		// Euclidean distance is a specific case of minowski equation, in order to save code we just use it.
		return MinkowskiDistanceCalculator(2).calculate(v1, v2);
	} 
	
	double ManhattanDistanceCalculator::calculate(cVectorRef v1, cVectorRef v2) const {
		// Manhatan equation is a specific case of minowski equation, in order to save code we just use it.
		return MinkowskiDistanceCalculator(1).calculate(v1, v2);
	}
	
	double ChebyshevDistanceCalculator::calculate(cVectorRef v1, cVectorRef v2) const {
		double dist = 0;
		const unsigned int len = v1.size() >= v2.size() ? v2.size() : v1.size();
		for (int i = 0; i < len; i++) {
			double tmp = std::abs(v1[i] - v2[i]);
			if (tmp > dist)
				dist = tmp;
		}
		
		return dist;
	}
	
	double CanberraDistanceCalculator::calculate(cVectorRef v1, cVectorRef v2) const {
		// The case where both coordinates are 0 is defined as 0/0 = 0
		double canberraSum = 0;
		
		const unsigned int len = v1.size() >= v2.size() ? v2.size() : v1.size();
		for (int i = 0; i < len; i++)
			if (!(v1[i] == 0 && v2[i] == 0))
				canberraSum += std::abs(v1[i] - v2[i]) / (std::abs(v1[i]) + std::abs(v2[i]));
		
		return canberraSum;
	}
	
	MinkowskiDistanceCalculator::MinkowskiDistanceCalculator(const int& p) : p(p) {}
	
	double MinkowskiDistanceCalculator::calculate(cVectorRef v1, cVectorRef v2) const {
		double distance = 0;
		const unsigned int len = v1.size() >= v2.size() ? v2.size() : v1.size();
		for (int i = 0; i < len; i++) {
			distance += std::pow(std::abs(v1[i] - v2[i]), p);
		}
		
		return pow(distance, 1.0 / p);
	}
	
	void MinkowskiDistanceCalculator::setP(const int& p) {
		this->p = p;
	}
	
	int MinkowskiDistanceCalculator::getP() const {
		return p;
	}
	
}
