#include "VectorDistanceCalculator.h"
#include "Vector.h"
#include <cmath>


double VectorDistanceCalculator::euclidean(Vector v1, Vector v2) {
	//this is the calculation of euclidean distance
	return sqrt(pow((v1.getX() - v2.getX()),2) + pow((v1.getY() - v2.getY()),2)
	 + pow((v1.getZ() - v2.getZ()),2));
}


double VectorDistanceCalculator::manhattan(Vector v1, Vector v2) {
	//manhatan equation is a specific case of minowski equation,in order to save code we just use it
	return minkowski(v1, v2, 1);
}


double VectorDistanceCalculator::minkowski(Vector v1, Vector v2, int p) {
	double distance = 0;
	for (int i = 0; i < 3; i++) {
		distance += pow(abs(v1.[i],v2.[i]), p);
	}
	
	return pow(distance, 1 / p);
}