#include "VectorDataSet.h"
#include "StringValidator.h"

namespace VectorCalculation {
	
	
	std::vector<std::string> VectorDataSet::createStringVector(std::string s) {
		std::string tmp = "";
		std::vector<std::string> vec;
		for(int i = 0 ; i < s.length(); i++) {
			if(s[i] == ','){
				vec.push_back(tmp);
				tmp.clear();
			} else {
				tmp.push_back(s[i]);
			}
		}
		return vec;
	}
	
	DataEntry VectorDataSet::createDataEntry(std::string s) {
		std::vector<std::string> sVec = createStringVector(s);
		DataEntry dEntry;
		int i = 0;
		for(i; i < sVec.size() - 1;i ++){
			dEntry.first.push_back(std::stod(sVec[i]));
		}
		dEntry.second = sVec[i];
		return dEntry;
	}
	
	
	void VectorDataSet::createDentryVectors(std::istream &file) {
		std::string line = "";
		//this loop will go on untill there is no more data from user.
		while (std::getline(file, line)) {
			dataset.push_back(createDataEntry(line));
			line.clear();
		}
	}
	
	VectorDataSet::VectorDataSet(std::istream &file) {
		createDentryVectors(file);
	}
}





