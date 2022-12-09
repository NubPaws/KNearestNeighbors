#include <map>
#include <string>
#include <algorithm>

#include "KNearestNeighbors.h"
#include "VectorDataSet.h"
#include "Types.h"

KNearestNeighbors::KNearestNeighbors(VectorDataSet dataset, VectorDistance::Calculator::Type distType)
	: dataset(dataset), distance(distType) {
	
}

std::string KNearestNeighbors::find(const std::vector<double>& item, const size_t k) {
	findClosestK(item, k);
	
	const size_t len = (k >= dataset.size()) ? dataset.size() : k;
	
	std::map<std::string, size_t> types;
	
	for (size_t i = 0; i < len; i++) {
		std::string name = dataset[i].second;
		if (types.find(name) == types.end())
			types[name] = 0;
		types[name] += 1;
	}
	
	std::string result = "";
	size_t resultCount = 0;
	for (const auto& type : types) {
		if (type.second > resultCount) {
			result = type.first;
			resultCount = type.second;
		}
	}
	
	return result;
}

void KNearestNeighbors::findClosestK(const std::vector<double>& item, size_t k) {
	const size_t len = dataset.size();
	if (k >= len)
		return;
	
	// Pre-calculate all distances. Then we can use them later on.
	std::vector<double> distances;
	for (size_t i = 0; i < dataset.size(); i++) {
		distances.push_back(distance(item, dataset[i].first));
	}
	
	size_t foundCount = 1;
	size_t largestIndex = 0;
	double d1 = distances[largestIndex];
	double d2;
	for (size_t i = 1; i < len; i++) {
		double d2 = distances[i];
		// If we have yet to find k elements:
		if (foundCount < k) {
			dataset.swap(foundCount, i);
			std::swap(distances[foundCount], distances[i]);
			if (d1 < d2)
				largestIndex = foundCount;
			foundCount++;
		} else if (d1 > d2) {
			// Swap them, get the new max. The index will be in the same spot.
			dataset.swap(largestIndex, i);
			std::swap(distances[largestIndex], distances[i]);
			largestIndex = findMaxDistanceIndex(distances, 0, k);
			d1 = distances[largestIndex];;
		}
	}
}

size_t KNearestNeighbors::findMaxDistanceIndex(const std::vector<double>& distances, const size_t& i, const size_t& j) const {
	double d1 = distances[i];
	double d2;
	size_t maxIndex = i;
	for (size_t k = i; k <= j; k++) {
		d2 = distances[k];
		if (d1 < d2) {
			maxIndex = k;
			d1 = d2;
		}
	}
	return maxIndex;
}
