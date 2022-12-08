#include "StringValidator.h"

bool StringValidator::isDouble(const std::string& str) {
	// Flags to check if the number is a negative and if it has a decimal point.
	bool isNegative = str[0] == '-';
	bool hasDecimal = false;
	
	/*
	Start the loop from the 0th index if the number is not a negative number. Otherwise
	start it from the 1st index. For each index check if the string only contains numbers
	and 1 decimal point. If not return out a false value.
	*/
	for (int i = isNegative; i < str.length(); i++) {
		if ((str[i] < '0' || '9' < str[i]) && str[i] != '.')
			return false;
		
		if (str[i] == '.') {
			if (hasDecimal)
				return false;
			hasDecimal = true;
		}
	}
	
	// If the string only contains a - and a . then return false, otherwise it is a valid string
	// and we can return true.
	return str.length() != (isNegative + hasDecimal);
}

bool StringValidator::isInt(const std::string& str) {
	if (str.length() == 0)
		return false;
	
	bool isNegative = str[0] == '-';
	
	/*
	Start the loop from the 0th index if the number is not a negative number. Otherwise
	start it from the 1st index. For each index check if the string only contains numbers
	and 1 decimal point. If not return out a false value.
	*/
	for (int i = isNegative; i < str.length(); i++)
		if (str[i] < '0' || '9' < str[i])
			return false;
	
	return str.length() != isNegative;
}
