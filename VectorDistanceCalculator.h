#ifndef _VECTOR_DISTANCE_CALCULATOR
#define _VECTOR_DISTANCE_CALCULATOR

#include "Vector.h"

namespace VectorDistanceCalculator {
	
	/**
	 * @brief calculates the euclidean distance of two vectors.
	 * the euclidean equation is a specific case of minowski equation,where p is equals to 2,in order to save code we just use it.
	 * the euclidean distance is the square root of the sum of all the distances of two vectors cooardinates in the power of 2.
	 * 
	 * @param v1 the first vector.
	 * @param v2 the second vector.
	*/
	double euclidean(const Vector v1, const Vector v2);
	
	/**
	 * @brief calculates the manhattan distance of two vectors.
	 * the manhattan equation is a specific case of minowski equation,in order to save code we just use it.
	 * the manhattan distance is the sum of all the distances of two vectors cooardinates.
	 * 
	 * @param v1 the first vector.
	 * @param v2 the second vector.
	*/
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
	
	/**
	 * @brief calculates the minkowski distance of two vectors.
	 * the minkowski equation calculate the sum of of |v1[i]-v2[i]| in the power of p where v1,v2 represents the vecotrs,
	 * and the i represnt the axis(i = 0 is x,i = i is y and so on)  
	 * then it returns the sum in the power of 1/p
	 *
	 * @param v1 the first vector.
	 * @param v2 the second vector.
	 * @param p the order of the distnace.
	*/
	double minkowski(const Vector v1, const Vector v2, const int p);
	
}

#endif // _VECTOR_DISTANCE_CALCULATOR
