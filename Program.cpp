#include <iostream>
#include "Vector.h"
#include "VectorDistanceCalculator.h"

int main() {
	
	Vector v1(1, 2, 3);
	Vector v2(3, 2, 1);
	
	VectorDistanceCalculator::euclidean(v1, v2);
	
}
