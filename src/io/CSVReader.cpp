#include <iostream>
#include <string>
#include <cstdlib>

#include "CSVReader.h"
#include "Types.h"
#include "StringUtils.h"

CSVReader::CSVReader(const std::string& filename)
	: length(0), in(filename, std::ios::in) {
	
	if (!in.is_open()) {
		std::cout << "Failed loading the file " << filename << std::endl;
		std::exit(0);
	}
	
	loadNextLine();
	length = line.size();
}

CSVReader::~CSVReader() {
	if (in.is_open())
		in.close();
}

std::vector<std::string> CSVReader::readLine() {
	std::vector<std::string> result(line);
	loadNextLine();
	return result;
}

void CSVReader::loadNextLine() {
	line.clear();
	
	if (in.eof())
		return;
	
	std::string ln = "";
	std::getline(in, ln);
	
	if (in.eof()) {
		in.close();
	}
	
	const std::string delimeter = ",";
	
	size_t pos;
	std::string token;
	while ((pos = ln.find(delimeter)) != std::string::npos) {
		token = ln.substr(0, pos);
		line.push_back(token);
		ln.erase(0, pos + delimeter.length());
	}
	ln = Utils::trimWhiteSpace(ln);
	line.push_back(ln);
}
