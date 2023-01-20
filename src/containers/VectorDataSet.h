#ifndef _VECTOR_DATA_SET_H
#define _VECTOR_DATA_SET_H

#include <string>
#include <sstream>
#include <vector>

#include "Types.h"

class VectorDataSet {
public:
	typedef std::pair<Vector, std::string> DataEntry;
private:
	std::vector<DataEntry> dataset;
public:
	VectorDataSet();
	
	VectorDataSet(std::stringstream& buffer, bool isClassified = true);
	
	void set(std::stringstream& buffer, bool isClassified);
	
	size_t width() const;
	
	size_t size() const;
	
	void swap(const size_t& i, const size_t& j);
	
	void setEntryType(const size_t& i, const std::string& type);
	
	const DataEntry& operator[](size_t index) const;
	
};

#endif // _VECTOR_DATA_SET_H
