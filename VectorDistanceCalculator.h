#ifndef _VECTOR_DISTANCE_CALCULATOR
#define _VECTOR_DISTANCE_CALCULATOR

#include "Vector.h"

namespace VectorDistanceCalculator {
	
	double euclidean(Vector v1, Vector v2);
	
	double manhattan(Vector v1, Vector v2);
	
	double chebyshev(Vector v1, Vector v2);
	
	double canberra(Vector v1, Vector v2);
	
	double minkowski(Vector v1, Vector v2);
	
}

#endif // _VECTOR_DISTANCE_CALCULATOR
