#include <map>
#include <string>

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
	
	double d1, d2;
	for (size_t i = 0; i < k; i++) {
		d1 = distance(item, dataset[i].first);
		for (size_t j = i; j < len; j++) {
			d2 = distance(item, dataset[j].first);
			
			if (d1 > d2) {
				dataset.swap(i, j);
				d1 = d2;
			}
		}
	}
}
