#include <vector>
#include <cmath>
#include <string>
#include "VectorDistance.h"

namespace VectorDistance {
	
	// To make the code a bit shorter and more readable.
	using cVectorRef = const std::vector<double>&;
	
	double Calculator::operator()(cVectorRef v1, cVectorRef v2) const {
		return this->calculate(v1, v2);
	}
	
	std::unique_ptr<Calculator> Calculator::getCalculator(const std::string& name) {
		if (name == "AUC")
			return std::unique_ptr<Calculator>(new EuclideanCalculator());
		if (name == "MAN")
			return std::unique_ptr<Calculator>(new ManhattanCalculator());
		if (name == "CHB")
			return std::unique_ptr<Calculator>(new ChebyshevCalculator());
		if (name == "CAN")
			return std::unique_ptr<Calculator>(new CanberraCalculator());
		if (name == "MIN")
			return std::unique_ptr<Calculator>(new MinkowskiCalculator());
		return std::unique_ptr<Calculator>(nullptr);
	}
	
	double EuclideanCalculator::calculate(cVectorRef v1, cVectorRef v2) const {
		// Euclidean distance is a specific case of minowski equation, in order to save code we just use it.
		return MinkowskiCalculator(2).calculate(v1, v2);
	} 
	
	double ManhattanCalculator::calculate(cVectorRef v1, cVectorRef v2) const {
		// Manhatan equation is a specific case of minowski equation, in order to save code we just use it.
		return MinkowskiCalculator(1).calculate(v1, v2);
	}
	
	double ChebyshevCalculator::calculate(cVectorRef v1, cVectorRef v2) const {
		double dist = 0;
		const unsigned int len = v1.size() >= v2.size() ? v2.size() : v1.size();
		for (int i = 0; i < len; i++) {
			double tmp = std::abs(v1[i] - v2[i]);
			if (tmp > dist)
				dist = tmp;
		}
		
		return dist;
	}
	
	double CanberraCalculator::calculate(cVectorRef v1, cVectorRef v2) const {
		// The case where both coordinates are 0 is defined as 0/0 = 0
		double canberraSum = 0;
		
		const unsigned int len = v1.size() >= v2.size() ? v2.size() : v1.size();
		for (int i = 0; i < len; i++)
			if (!(v1[i] == 0 && v2[i] == 0))
				canberraSum += std::abs(v1[i] - v2[i]) / (std::abs(v1[i]) + std::abs(v2[i]));
		
		return canberraSum;
	}
	
	MinkowskiCalculator::MinkowskiCalculator(const int& p) : p(p) {}
	
	double MinkowskiCalculator::calculate(cVectorRef v1, cVectorRef v2) const {
		double distance = 0;
		const unsigned int len = v1.size() >= v2.size() ? v2.size() : v1.size();
		for (int i = 0; i < len; i++) {
			distance += std::pow(std::abs(v1[i] - v2[i]), p);
		}
		
		return pow(distance, 1.0 / p);
	}
	
	void MinkowskiCalculator::setP(const int& p) {
		this->p = p;
	}
	
	int MinkowskiCalculator::getP() const {
		return p;
	}
	
}
