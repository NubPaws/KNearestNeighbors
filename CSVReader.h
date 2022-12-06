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
	CSVReader(const std::string& filename);
	~CSVReader();
	
	std::vector<std::string> readLine();
private:
	void loadNextLine();
};

#endif // _CSV_READER_H