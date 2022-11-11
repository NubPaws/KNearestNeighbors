#ifndef _VECTOR_DISTANCE_CALCULATOR
#define _VECTOR_DISTANCE_CALCULATOR

#include "Vector.h"

namespace VectorDistanceCalculator {
	
	double euclidean(const Vector v1, const Vector v2);
	
	double manhattan(const Vector v1, const Vector v2);
	
	/**
	 * @brief Calculates the Chebyshev distance of two vectors.
	 * The Chebyshev distance is the maximum of the distances in each one of the axis.
	 * 
	 * @param v1 The first vector.
	 * @param v2 The second vector.
	 * @return The Chebyshev distance of the two vectors.
	 */
	double chebyshev(const Vector v1, const Vector v2);
	
	/**
	 * @brief Calculates the Canberra distance of the two vectors.
	 * The Canberra distance is the sum of |pi-qi|/(|pi|-|qi|) where pi and qi are the values of vectors
	 * p and q in the i-th axis.
	 * 
	 * @param v1 The first vector.
	 * @param v2 The second vector.
	 * @return The Canberra distance of the two vectors.
	 */
	double canberra(const Vector v1, const Vector v2);
	
	double minkowski(const Vector v1, const Vector v2, const int p);
	
}

#endif // _VECTOR_DISTANCE_CALCULATOR
