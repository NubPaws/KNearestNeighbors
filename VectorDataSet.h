#ifndef _VECTOR_DATA_SET_H
#define _VECTOR_DATA_SET_H

#include <iostream>
#include <utility>
#include <string>
#include <vector>
#include <iterator>
#include <cstddef>

namespace VectorCalculation {
	typedef std::pair<std::vector<double>, std::string> DataEntry;

	class VectorDataSet {
	private:
		std::vector<DataEntry> dataset;
	public:
		VectorDataSet(std::istream file);
		
		std::size_t size() const;
		const DataEntry& operator[](std::size_t index) const;
	};
}

#endif // _VECTOR_DATA_SET_H
