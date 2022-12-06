#ifndef _VECTOR_DATA_SET_H
#define _VECTOR_DATA_SET_H

#include <string>
#include <vector>

namespace VectorCalculation {
	typedef std::pair<std::vector<double>, std::string> DataEntry;
	
	class VectorDataSet {
	private:
		std::vector<DataEntry> dataset;
	public:
		VectorDataSet(const std::string& filename);
		
		std::size_t size() const;
		
		void swap(const std::size_t& i, const std::size_t& j);
		
		const DataEntry& operator[](std::size_t index) const;
	};
}

#endif // _VECTOR_DATA_SET_H
