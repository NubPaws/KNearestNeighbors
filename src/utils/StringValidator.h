#ifndef _STRING_VALIDATOR_H
#define _STRING_VALIDATOR_H

#include <string>

namespace StringValidator {
	/**
	 * @brief Checks if a string can be converted to a double.
	 * 
	 * @param str The string to check against.
	 * @return true If the string can be converted to a double.
	 * @return false If the string cannot be converted to a double.
	 */
	bool isDouble(const std::string& str);
	
	/**
	 * @brief Checks if a string can be converted to an int.
	 * 
	 * @param str The string to check against.
	 * @return true If the string can be converted to an int.
	 * @return false If the string cannot be converted to an int.
	 */
	bool isInt(const std::string& str);
}

#endif // _STRING_VALIDATOR_H
