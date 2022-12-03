#include "VectorDataSet.h"
#include "StringValidator.h"

namespace VectorCalculation {
	int VectorDataSet::commasCouter(std::string s) {
		int counter = 0;
		for (int i = 0; i < s.length(); i++) {
			if (s[i] == ',') {
				counter++;
			}
		}
		return counter;
	}
	
	DataEntry VectorDataSet::createDataEntry(std::string s) {
		std::string pName = "";
		std::string pVector = "";
		
		std::vector<double> dEntryFirst;
		DataEntry toReturn;
		int numOfCommas = commasCouter(s);
		int i = 0;
		
		//this while loop will create the left side of the dataEntry (vecotr)
		while (s[i]) {
			//when num of commas is 0 we are on the name part of the string
			if (numOfCommas == 0) {
				break;
			}
			if (std::isspace(s[i++])) {
				//checks if the string collected is indeed in a form of "double"
				if (!StringValidator::isDouble(pVector)) {
					return toReturn; //TODO ask rami how to return null
				} else {
					dEntryFirst.push_back(std::stod(pVector));
					pVector.clear();
				}
			} else {
				//push the next character to the string
				pVector.push_back(s[i]);
			}
			numOfCommas--;
		}
		
		// this while loop right-side of dataEntery (the name of plant)
		while (s[i]) {
			pName.push_back(s[i]);
			i++;
		}
		
		//TODO add function that checks if the name is vaild.
		toReturn.second = pName;
		return toReturn;
	}
	
	void VectorDataSet::createDentryVectors(std::istream &file) {
		std::string line = "";
		
		//this loop will go on untill there is no more data from user.
		while (std::getline(file, line)) {
			//TODO if dentery == null handle it.
			dataset.push_back(createDataEntry(line));
			line.clear();
		}
	}
	
	VectorDataSet::VectorDataSet(std::istream &file) {
		createDentryVectors(file);
	}
}





