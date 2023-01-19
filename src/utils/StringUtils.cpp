#include <cctype>
#include <iterator>
#include <cstdlib>

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
	
	std::vector<std::string> seperate(std::string& str, const std::string& sep) {
		std::vector<std::string> line;
		size_t pos = 0;
		std::string token;
		while ((pos = str.find(sep)) != std::string::npos) {
			token = str.substr(0, pos);
			line.push_back(token);
			str.erase(0, pos + sep.length());
		}
		str = trimWhiteSpace(str);
		line.push_back(str);
		
		return line;
	}
	
}
