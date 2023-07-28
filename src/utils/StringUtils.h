#ifndef _STRING_UTILS_H
#define _STRING_UTILS_H

#include "StringValidator.h"

#include <vector>
#include <string>
#include <sstream>

namespace Utils {
	/**
	 * @brief Turns a line into a string vector, seperates them based
	 * on whitespaces.
	 * 
	 * @param line The line to turn into a vector.
	 * @return std::vector<std::string> The new vector containing
	 * only the words.
	 */
	std::vector<std::string> readLineAsVector(std::string line);
	
	/**
	 * @brief Trims whitespaces from a string at the start and
	 * at the end of it.
	 * 
	 * @param str The string to trim the whitespace from.
	 * @return std::string The trimmed string.
	 */
	std::string trimWhiteSpace(std::string str);
	
	/**
	 * @brief Seperates a string based on a given seperator.
	 * 
	 * @param str The string to seperate.
	 * @param sep THe seperator (or delimiter if you want to).
	 * @return std::vector<std::string> The seperated string as a
	 * vector array of strings.
	 */
	std::vector<std::string> seperate(std::string& str, const std::string& sep);
	
}
#endif // _STRING_UTILS_H
