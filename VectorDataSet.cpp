#include <cstddef>
#include <cstdlib>
#include <iostream>

#include "VectorDataSet.h"
#include "StringValidator.h"
#include "CSVReader.h"

namespace VectorCalculation {
	
	VectorDataSet::VectorDataSet(const std::string &filename)
		: dataset() {
		CSVReader reader(filename);
		
		std::vector<std::string> line = reader.readLine();
		while (!line.empty()) {
			DataEntry entry;
			entry.second = line[line.size() - 1];
			line.pop_back();
			
			for (std::size_t i = 0; i < line.size(); i++) {
				if (StringValidator::isDouble(line[i])) {
					entry.first.push_back(std::stod(line[i]));
				} else {
					std::cout << "Problem with the format of the file in line "
						<< dataset.size() + 1 << "." << std::endl;
					std::exit(0);
				}
			}
			
			dataset.push_back(entry);
		}
		
		for (std::size_t i = 1; i < dataset.size(); i++) {
			if (dataset[i].first.size() != dataset[0].first.size()) {
				std::cout << "Problem with the number of parameters in line "
					<< i << "." << std::endl;
				std::exit(0);
			}void swap(const std::size_t& i, const std::size_t& j);
		}
	}
	
	
	std::size_t VectorDataSet::size() const {
		return dataset.size();
	}
	
	void VectorDataSet::swap(const std::size_t& i, const std::size_t& j) {
		DataEntry tmp = dataset[i];
		dataset[i] = dataset[j];
		dataset[j] = tmp;
	}
	
	const DataEntry& VectorDataSet::operator[](std::size_t index) const {
		if (index < dataset.size())
			return dataset[index];
		return DataEntry();
	}
	
}