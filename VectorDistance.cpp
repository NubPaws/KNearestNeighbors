#include <vector>
#include <cmath>
#include <string>

#include "VectorDistance.h"
#include "Types.h"

namespace VectorDistance {
	
	// To make the code a bit shorter and more readable.
	using cVectorRef = const std::vector<double>&;
	
	const std::string Calculator::TYPES[] = {"AUC", "MAN", "CHB", "CAN", "MIN"};
	
	Calculator::Type Calculator::getType(const std::string& name) {
		for (size_t i = 0; i < (size_t)Type::Empty; i++)
			if (name == TYPES[i])
				return (Type)i;
		return Type::Empty;
	}
	
	Calculator::Calculator()
		: distCalc(nullptr), type("") {
	}
	
	Calculator::Calculator(const Calculator::Type& type)
		: distCalc(nullptr), type() {
		if (type != Type::Empty)
			set(TYPES[(size_t)type]);
	}
	
	Calculator::Calculator(const Calculator& c)
		: distCalc(nullptr), type("") {
		set(c.type);
	}
	
	Calculator& Calculator::operator=(const Calculator& other) {
		set(other.type);
		return *this;
	}
	
	Calculator::Calculator(Calculator&& other) noexcept
		: distCalc(other.distCalc), type(other.type) {
		other.distCalc = nullptr;
		other.type = std::string();
	}
	
	Calculator& Calculator::operator=(Calculator&& other) noexcept {
		distCalc = other.distCalc;
		type = other.type;
		
		other.distCalc = nullptr;
		other.type = std::string();
		
		return *this;
	}
	
	
	Calculator::~Calculator() {
		if (distCalc)
			delete distCalc;
	}
	
	void Calculator::set(const std::string& name, const int& p) {
		type = name;
		if (distCalc)
			delete distCalc;
		
		if (name == TYPES[(size_t)Type::Euclidean])
			distCalc = new EuclideanCalculator();
		else if (name == TYPES[(size_t)Type::Manhattan])
			distCalc = new ManhattanCalculator();
		else if (name == TYPES[(size_t)Type::Chebyshev])
			distCalc = new ChebyshevCalculator();
		else if (name == TYPES[(size_t)Type::Canberra])
			distCalc = new CanberraCalculator();
		else if (name == TYPES[(size_t)Type::Minkowski])
			distCalc = new MinkowskiCalculator(p);
		else
			distCalc = nullptr;
	}
	
	double Calculator::operator()(cVectorRef v1, cVectorRef v2) const {
		return distCalc->calculate(v1, v2);
	}
	
	double DistanceCalculator::operator()(cVectorRef v1, cVectorRef v2) const {
		return this->calculate(v1, v2);
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
