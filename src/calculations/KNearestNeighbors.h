#ifndef _K_NEAREST_NEIGHBORS_H
#define _K_NEAREST_NEIGHBORS_H

#include <string>

#include "containers/VectorDataSet.h"
#include "VectorDistance.h"
#include "Types.h"

class KNearestNeighbors {
private:
	VectorDataSet dataset;
	VectorDistance::Calculator distance;
public:
	/**
	 * @brief Construct a new KNearestNeighbors object
	 * 
	 * @param dataset A VectorDataSet containing the vectors to use as our knowledge.
	 * @param distType The distance calculation type to use.
	 */
	KNearestNeighbors(VectorDataSet dataset, VectorDistance::Calculator::Type distType);
	
	/**
	 * @brief Finds the most probably type of the item that was given.
	 * Changes the dataset it has.
	 * 
	 * @param item The item to check against.
	 * @param k How deep to do the search.
	 * @return std::string The name of what the item is like.
	 */
	std::string find(const std::vector<double>& item, const size_t k);
	
	/**
	 * @brief Set the distance calculation method.
	 * 
	 * @param distType The type to set against.
	 */
	void setDistanceType(VectorDistance::Calculator::Type distType);
private:
	/**
	 * @brief Sets the dataset to store all the closest vectors to be at the
	 * start of the list. Then uses that to infer the type of the vector item.
	 * 
	 * @param item The vector get the closest items to it.
	 * @param k How many close items you need.
	 */
	void findClosestK(const std::vector<double>& item, size_t k);
	
	/**
	 * @brief Finds the index of the farthest away vector.
	 * 
	 * @param distances A list of distances to check against.
	 * @param i The start of the check.
	 * @param j The end of the check.
	 * @return size_t The index of the farthest away vector.
	 */
	size_t findMaxDistanceIndex(const std::vector<double>& distances, const size_t& i, const size_t& j) const;
};

#endif // _K_NEAREST_NEIGHBORS_H