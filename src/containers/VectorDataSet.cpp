#include <cstddef>
#include <cstdlib>
#include <iostream>

#include "Types.h"
#include "VectorDataSet.h"
#include "StringValidator.h"
#include "CSVReader.h"
#include "StringUtils.h"

VectorDataSet::VectorDataSet()
	: dataset() {
	
}

VectorDataSet::VectorDataSet(std::string& input, bool isClassified)
	: dataset() {
	this->set(input, isClassified);
}

bool VectorDataSet::set(std::string& input, bool isClassified) {
	for (auto it = input.begin(); it != input.end(); it++) {
		if (*it == '\r')
			input.erase(it, it);
	}
	std::vector<std::string> buffer = Utils::seperate(input, "\n");
	
	while (!buffer.empty()) {
		std::vector<std::string> line = Utils::seperate(buffer[0], ",");
		
		DataEntry entry;
		
		if (isClassified) {
			entry.second = line[line.size() - 1];
			line.pop_back();
		} else {
			entry.second = ""; // Emptry string.
		}
		
		for (size_t i = 0; i < line.size(); i++) {
			if (Utils::isDouble(line[i])) {
				entry.first.push_back(std::stod(line[i]));
			} else {
				std::cerr << "Problem with the format of the file in line "
					<< dataset.size() + 1 << "." << std::endl;
				std::exit(0);
			}
		}
		
		dataset.push_back(entry);
		buffer.erase(buffer.begin());
	}
	
	for (size_t i = 1; i < dataset.size(); i++) {
		if (dataset[i].first.size() != dataset[i - 1].first.size()) {
			std::cout << "Problem with the number of parameters in line "
				<< i << "." << std::endl;
			return false;
		}
	}
	return true;
}

size_t VectorDataSet::width() const {
	if (dataset.empty())
		return 0;
	return dataset[0].first.size();
}

size_t VectorDataSet::size() const {
	return dataset.size();
}

void VectorDataSet::clear() {
	dataset.clear();
}

void VectorDataSet::swap(const size_t& i, const size_t& j) {
	DataEntry tmp = dataset[i];
	dataset[i] = dataset[j];
	dataset[j] = tmp;
}

void VectorDataSet::setEntryType(const size_t& i, const std::string& type) {
	dataset[i].second = type;
}


const VectorDataSet::DataEntry& VectorDataSet::operator[](size_t index) const {
	if (index < dataset.size())
		return dataset[index];
	return dataset[0];
}