#include <cctype>
#include <iterator>

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
	
	std::string trimWhiteSpace(std::string str) {
		auto start = str.begin();
		while (start != str.end() && std::isspace(*start)) {
			start++;
		}
		
		auto end = str.end();
		do {
			end--;
		} while (std::distance(start, end) > 0 && std::isspace(*end));
		
		return std::string(start, end + 1); // Capiche?
	}
	
}
