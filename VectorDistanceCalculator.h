#ifndef _VECTOR_DISTANCE_CALCULATOR
#define _VECTOR_DISTANCE_CALCULATOR

#include "Vector.h"

namespace VectorDistanceCalculator {
	
	double euclidean(const Vector v1, const Vector v2);
	
	double manhattan(const Vector v1, const Vector v2);
	
	double chebyshev(const Vector v1, const Vector v2);
	
	double canberra(const Vector v1, const Vector v2);
	
	double minkowski(const Vector v1, const Vector v2, const double p);
	
}

#endif // _VECTOR_DISTANCE_CALCULATOR
