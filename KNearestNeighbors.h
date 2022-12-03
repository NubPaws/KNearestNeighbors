#ifndef _K_NEAREST_NEIGHBORS
#define _K_NEAREST_NEIGHBORS

#include <string>
#include <cstddef>

#include "VectorDataSet.h"
#include "VectorDistanceCalculator.h"


namespace VectorCalculation {
	
	class KNearestNeighbors {
	private:
		VectorDataSet dataset;
		DistanceCalculator &distance;
	public:
		KNearestNeighbors(VectorDataSet dataset, DistanceCalculator &distance);
		
		std::string find(std::size_t k) const;
	private:
		
	};
	
}

#endif // _K_NEAREST_NEIGHBORS
