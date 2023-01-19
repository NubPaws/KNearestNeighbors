#include <map>
#include <string>
#include <utility>
#include <iostream>

#include "KNearestNeighbors.h"
#include "VectorDataSet.h"
#include "Types.h"

using CalcType = VectorDistance::Calculator::Type;

// Default values given by the assignment.
KNearestNeighbors::KNearestNeighbors()
	: dataset(), distance(CalcType::Euclidean), k(5) {
	
}

KNearestNeighbors::KNearestNeighbors(VectorDataSet dataset, CalcType distType, const size_t k)
	: dataset(dataset), distance(distType), k(k) {
	
}

std::string KNearestNeighbors::find(const Vector& item) {
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

void KNearestNeighbors::setDistanceType(CalcType distType) {
	distance.set(distType);
}

void KNearestNeighbors::findClosestK(const Vector& item, size_t k) {
	const size_t len = dataset.size();
	if (k >= len)
		return;
	
	// Pre-calculate all distances. Then we can use them later on.
	Vector distances;
	for (size_t i = 0; i < dataset.size(); i++) {
		distances.push_back(distance(item, dataset[i].first));
	}
	
	size_t foundCount = 1;
	size_t largestIndex = 0;
	double d1 = distances[largestIndex];
	double d2;
	for (size_t i = 1; i < len; i++) {
		d2 = distances[i];
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

size_t KNearestNeighbors::findMaxDistanceIndex(const Vector& distances, size_t i, size_t j) const {
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

int KNearestNeighbors::getK() const {
	return k;
}

void KNearestNeighbors::setK(size_t k) {
	this->k = k;
}

std::string KNearestNeighbors::getMetric() const {
	return distance.getMetric();
}

bool KNearestNeighbors::isValidDataSet() const {
	return dataset.size() != 0;
}
