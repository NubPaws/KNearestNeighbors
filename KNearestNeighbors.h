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
		
		std::string find(const std::vector<double>& item, const std::size_t k);
	private:
		void findClosestK(const std::vector<double>& item, std::size_t k);
	};
	
}

#endif // _K_NEAREST_NEIGHBORS
