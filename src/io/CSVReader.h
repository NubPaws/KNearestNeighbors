#ifndef _CSV_READER_H
#define _CSV_READER_H

#include <string>
#include <vector>
#include <cstddef>
#include <fstream>

class CSVReader {
private:
	std::size_t length;
	std::ifstream in;
	std::vector<std::string> line;
public:
	/**
	 * @brief Construct a new CSVReader object.
	 * 
	 * @param filename The name of the csv file to read.
	 */
	CSVReader(const std::string& filename);
	~CSVReader();
	
	/**
	 * @brief Reads the next line in the csv file.
	 * 
	 * @return std::vector<std::string> Empty if we reached the end of the file.
	 * Otherwise returns the line as a vector.
	 */
	std::vector<std::string> readLine();
private:
	/**
	 * @brief Helper function to load our vector memeber with the new line.
	 * This function will set it to be an empty vector if there are no more
	 * lines to read.
	 */
	void loadNextLine();
};

#endif // _CSV_READER_H