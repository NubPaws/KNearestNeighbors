#ifndef _K_NEAREST_NEIGHBORS
#define _K_NEAREST_NEIGHBORS

#include <string>
#include <cstddef>

#include "VectorDataSet.h"
#include "VectorDistance.h"

class KNearestNeighbors {
private:
	VectorDataSet dataset;
	VectorDistance::Calculator &distance;
public:
	KNearestNeighbors(VectorDataSet dataset, VectorDistance::Calculator &distance);
	
	std::string find(const std::vector<double>& item, const std::size_t k);
private:
	void findClosestK(const std::vector<double>& item, std::size_t k);
};

#endif // _K_NEAREST_NEIGHBORS
