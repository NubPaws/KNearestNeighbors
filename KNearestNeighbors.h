#ifndef _K_NEAREST_NEIGHBORS
#define _K_NEAREST_NEIGHBORS

#include <string>

#include "VectorDataSet.h"
#include "VectorDistance.h"
#include "Types.h"

class KNearestNeighbors {
private:
	VectorDataSet dataset;
	VectorDistance::Calculator distance;
public:
	KNearestNeighbors(VectorDataSet dataset, VectorDistance::Calculator::Type distType);
	
	std::string find(const std::vector<double>& item, const size_t k);
private:
	void findClosestK(const std::vector<double>& item, size_t k);
	
	size_t findMaxDistanceIndex(const std::vector<double>& distances, const size_t& i, const size_t& j) const;
};

#endif // _K_NEAREST_NEIGHBORS
