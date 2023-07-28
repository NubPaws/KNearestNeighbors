#include <vector>
#include <cmath>
#include <string>

#include "VectorDistance.h"
#include "Types.h"

namespace VectorDistance {
	
	const std::string Calculator::TYPES[] = {"AUC", "MAN", "CHB", "CAN", "MIN"};
	
	Calculator::Type Calculator::getType(const std::string& name) {
		for (size_t i = 0; i < (size_t)Type::Empty; i++)
			if (name == TYPES[i])
				return (Type)i;
		return Type::Empty;
	}
	
	Calculator::Calculator()
		: distCalc(nullptr), type(Type::Empty) {
	}
	
	Calculator::Calculator(const Calculator::Type& type)
		: distCalc(nullptr), type(Type::Empty) {
		set(type);
	}
	
	Calculator::Calculator(const Calculator& other)
		: distCalc(nullptr), type(Type::Empty) {
		set(other.type);
	}
	
	Calculator& Calculator::operator=(const Calculator& other) {
		set(other.type);
		return *this;
	}
	
	Calculator::Calculator(Calculator&& other) noexcept
		: distCalc(other.distCalc), type(other.type) {
		other.distCalc = nullptr;
		other.type = Type::Empty;
	}
	
	Calculator& Calculator::operator=(Calculator&& other) noexcept {
		distCalc = other.distCalc;
		type = other.type;
		
		other.distCalc = nullptr;
		other.type = Type::Empty;
		
		return *this;
	}
	
	
	Calculator::~Calculator() {
		if (distCalc)
			delete distCalc;
	}
	
	void Calculator::set(const Calculator::Type& type, const int& p) {
		this->type = type;
		if (distCalc)
			delete distCalc;
		
		switch (type) {
			case Type::Euclidean:
				distCalc = new EuclideanCalculator();
				break;
			case Type::Manhattan:
				distCalc = new ManhattanCalculator();
				break;
			case Type::Chebyshev:
				distCalc = new ChebyshevCalculator();
				break;
			case Type::Canberra:
				distCalc = new CanberraCalculator();
				break;
			case Type::Minkowski:
				distCalc = new MinkowskiCalculator(p);
				break;
			default:
				distCalc = nullptr;
				break;
		}
	}
	
	std::string Calculator::getMetric() const {
		if (type == Type::Empty)
			return "";
		return TYPES[(size_t)type];
	}
	
	double Calculator::operator()(const Vector& v1, const Vector& v2) const {
		if (!distCalc)
			return -1;
		return distCalc->calculate(v1, v2);
	}
	
	double DistanceCalculator::operator()(const Vector& v1, const Vector& v2) const {
		return this->calculate(v1, v2);
	}
	
	double ChebyshevCalculator::calculate(const Vector& v1, const Vector& v2) const {
		double dist = 0;
		const unsigned int len = v1.size() >= v2.size() ? v2.size() : v1.size();
		for (int i = 0; i < len; i++) {
			double tmp = std::abs(v1[i] - v2[i]);
			if (tmp > dist)
				dist = tmp;
		}
		
		return dist;
	}
	
	double CanberraCalculator::calculate(const Vector& v1, const Vector& v2) const {
		// The case where both coordinates are 0 is defined as 0/0 = 0
		double canberraSum = 0;
		
		const unsigned int len = v1.size() >= v2.size() ? v2.size() : v1.size();
		for (int i = 0; i < len; i++)
			if (!(v1[i] == 0 && v2[i] == 0))
				canberraSum += std::abs(v1[i] - v2[i]) / (std::abs(v1[i]) + std::abs(v2[i]));
		
		return canberraSum;
	}
	
	MinkowskiCalculator::MinkowskiCalculator(const int& p) : p(p) {}
	
	double MinkowskiCalculator::calculate(const Vector& v1, const Vector& v2) const {
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
	
	EuclideanCalculator::EuclideanCalculator()
		: MinkowskiCalculator(2) {
	}
	
	ManhattanCalculator::ManhattanCalculator()
		: MinkowskiCalculator(1) {
	}
	
	
}
