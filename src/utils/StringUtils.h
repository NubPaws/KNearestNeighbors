#ifndef _STRING_UTILS_H
#define _STRING_UTILS_H

#include "StringValidator.h"

#include <vector>
#include <string>
#include <sstream>

namespace Utils {
	std::vector<std::string> readLineAsVector(std::string line);
	
	std::string trimWhiteSpace(std::string str);
	
	std::vector<std::string> seperate(std::string& str, const std::string& sep);
	
}
#endif // _STRING_UTILS_H
