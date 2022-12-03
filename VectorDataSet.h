#ifndef _VECTOR_DATA_SET_H
#define _VECTOR_DATA_SET_H

#include <iostream>
#include <utility>
#include <string>
#include <vector>
#include <iterator>
#include <cstddef>
#include "StringValidator.h"

namespace VectorCalculation {
	typedef std::pair<std::vector<double>, std::string> DataEntry;
	
	class VectorDataSet {
	private:
		std::vector<DataEntry> dataset;
		/**
		 * @brief this function will convert whole line into vector of strings,which will contain
		 * the words of the line without the commas.
		 *
		 * @param s
		 * @return vec- vector of strings.
		 */
		std::vector<std::string> createStringVector(std::string s);
		
		/**
		* @brief this is a function that creates the dataEntry pair.
		*
		* @param s string that represent the data from stream.
		* @return toReturn - the dataEntry pair.
		*/
		
		DataEntry createDataEntry(std::string s);
		
		/**
		 * @brief this function will create the dentrey vector which will contain all the dataEntry pairs.
		 * @param file the isstream.
		 */
		void createDentryVectors(std::istream &file);
		
	
	public:
		
		VectorDataSet(std::istream &file);
		
		std::size_t size() const;
		
		const DataEntry &operator[](std::size_t index) const;
	};
}

#endif // _VECTOR_DATA_SET_H
