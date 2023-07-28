#ifndef _VECTOR_DATA_SET_H
#define _VECTOR_DATA_SET_H

#include <string>
#include <sstream>
#include <vector>

#include "Types.h"

/**
 * @brief This class contains the vectors that are either classified or
 * unclassified as a list of data entries.
 * Allows us to do simple operations over the vectors.
 */
class VectorDataSet {
public:
	typedef std::pair<Vector, std::string> DataEntry;
private:
	std::vector<DataEntry> dataset;
public:
	/**
	 * @brief Construct a new empty Vector Data Set object.
	 */
	VectorDataSet();
	
	/**
	 * @brief Construct a new Vector Data Set object. Requires us to
	 * specify the input and whether or not that data is classified.
	 * 
	 * @param input The string to read into the data set.
	 * @param isClassified Whether or not the data is classified.
	 */
	VectorDataSet(std::string& input, bool isClassified = true);
	
	/**
	 * @brief Sets the dataset with the given input. Clears the vectors
	 * prior to setting them. This function allows us to not construct
	 * a new data set every time we need to update it with different values.
	 * 
	 * @param input The string to read into the data set.
	 * @param isClassified Whether or not the data is classified.
	 * @return true If setting the data has succeeded.
	 * @return false If setting the data has failed.
	 */
	bool set(std::string& input, bool isClassified);
	
	/**
	 * @brief Returns the amount of elements in each line, not including
	 * the classification if one exists.
	 * 
	 * @return size_t The width of the line.
	 */
	size_t width() const;
	
	/**
	 * @brief Returns the amount of entries in the data set.
	 * 
	 * @return size_t The number of entries in the data set.
	 */
	size_t size() const;
	
	/**
	 * @brief Clears the data set entirely.
	 */
	void clear();
	
	/**
	 * @brief Swaps two elements in the dataset, access the underlying
	 * vector in the data set.
	 * 
	 * @param i The first index.
	 * @param j The second index.
	 */
	void swap(const size_t& i, const size_t& j);
	
	/**
	 * @brief Set the type of the entry at a given index.
	 * 
	 * @param i The index to change the entry type at.
	 * @param type The new type.
	 */
	void setEntryType(const size_t& i, const std::string& type);
	
	/**
	 * @brief Access the data entry from the vector array..
	 * 
	 * @param index The index to access.
	 * @return const DataEntry& The data entry.
	 */
	const DataEntry& operator[](size_t index) const;
	
};

#endif // _VECTOR_DATA_SET_H
