#include "StringUtils.h"

namespace Utils {
	std::vector<std::string> readLineAsVector(std::string line) {
		std::istringstream iss(line);
		
		std::vector<std::string> result;
		
		std::string str;
		while (iss >> str)
			result.push_back(str);
		
		return result;
	}
}
