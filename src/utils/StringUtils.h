#ifndef _STRING_UTILS_H
#define _STRING_UTILS_H

#include "StringValidator.h"

#include <vector>
#include <string>
#include <sstream>

namespace Utils {
	std::vector<std::string> readLineAsVector(std::string line);
	
	std::string trimWhiteSpace(std::string str);
}
#endif // _STRING_UTILS_H
