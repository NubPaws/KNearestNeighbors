a286d66f CSVReader.cpp (NubPaws 2022-12-06 23:00:13 +0200  1) #include <iostream>
03dbc67e CSVReader.cpp (NubPaws 2022-12-08 17:08:21 +0200  2) #include <string>
a286d66f CSVReader.cpp (NubPaws 2022-12-06 23:00:13 +0200  3) #include <cstdlib>
a286d66f CSVReader.cpp (NubPaws 2022-12-06 23:00:13 +0200  4) 
03dbc67e CSVReader.cpp (NubPaws 2022-12-08 17:08:21 +0200  5) #include "CSVReader.h"
03dbc67e CSVReader.cpp (NubPaws 2022-12-08 17:08:21 +0200  6) #include "Types.h"
03dbc67e CSVReader.cpp (NubPaws 2022-12-08 17:08:21 +0200  7) 
a286d66f CSVReader.cpp (NubPaws 2022-12-06 23:00:13 +0200  8) CSVReader::CSVReader(const std::string& filename)
a286d66f CSVReader.cpp (NubPaws 2022-12-06 23:00:13 +0200  9) 	: length(0), in(filename, std::ios::in) {
a286d66f CSVReader.cpp (NubPaws 2022-12-06 23:00:13 +0200 10) 	
a286d66f CSVReader.cpp (NubPaws 2022-12-06 23:00:13 +0200 11) 	if (!in.is_open()) {
a286d66f CSVReader.cpp (NubPaws 2022-12-06 23:00:13 +0200 12) 		std::cout << "Failed loading the file " << filename << std::endl;
a286d66f CSVReader.cpp (NubPaws 2022-12-06 23:00:13 +0200 13) 		std::exit(0);
a286d66f CSVReader.cpp (NubPaws 2022-12-06 23:00:13 +0200 14) 	}
a286d66f CSVReader.cpp (NubPaws 2022-12-06 23:00:13 +0200 15) 	
a286d66f CSVReader.cpp (NubPaws 2022-12-06 23:00:13 +0200 16) 	loadNextLine();
a286d66f CSVReader.cpp (NubPaws 2022-12-06 23:00:13 +0200 17) 	length = line.size(); 
a286d66f CSVReader.cpp (NubPaws 2022-12-06 23:00:13 +0200 18) }
a286d66f CSVReader.cpp (NubPaws 2022-12-06 23:00:13 +0200 19) 
a286d66f CSVReader.cpp (NubPaws 2022-12-06 23:00:13 +0200 20) CSVReader::~CSVReader() {
a286d66f CSVReader.cpp (NubPaws 2022-12-06 23:00:13 +0200 21) 	if (in.is_open())
a286d66f CSVReader.cpp (NubPaws 2022-12-06 23:00:13 +0200 22) 		in.close();
a286d66f CSVReader.cpp (NubPaws 2022-12-06 23:00:13 +0200 23) }
a286d66f CSVReader.cpp (NubPaws 2022-12-06 23:00:13 +0200 24) 
a286d66f CSVReader.cpp (NubPaws 2022-12-06 23:00:13 +0200 25) std::vector<std::string> CSVReader::readLine() {
a286d66f CSVReader.cpp (NubPaws 2022-12-06 23:00:13 +0200 26) 	std::vector<std::string> result(line);
a286d66f CSVReader.cpp (NubPaws 2022-12-06 23:00:13 +0200 27) 	loadNextLine();
a286d66f CSVReader.cpp (NubPaws 2022-12-06 23:00:13 +0200 28) 	return result;
a286d66f CSVReader.cpp (NubPaws 2022-12-06 23:00:13 +0200 29) }
a286d66f CSVReader.cpp (NubPaws 2022-12-06 23:00:13 +0200 30) 
a286d66f CSVReader.cpp (NubPaws 2022-12-06 23:00:13 +0200 31) void CSVReader::loadNextLine() {
a286d66f CSVReader.cpp (NubPaws 2022-12-06 23:00:13 +0200 32) 	line.clear();
a286d66f CSVReader.cpp (NubPaws 2022-12-06 23:00:13 +0200 33) 	
a286d66f CSVReader.cpp (NubPaws 2022-12-06 23:00:13 +0200 34) 	if (in.eof())
a286d66f CSVReader.cpp (NubPaws 2022-12-06 23:00:13 +0200 35) 		return;
a286d66f CSVReader.cpp (NubPaws 2022-12-06 23:00:13 +0200 36) 	
a286d66f CSVReader.cpp (NubPaws 2022-12-06 23:00:13 +0200 37) 	std::string ln = "";
a286d66f CSVReader.cpp (NubPaws 2022-12-06 23:00:13 +0200 38) 	std::getline(in, ln);
a286d66f CSVReader.cpp (NubPaws 2022-12-06 23:00:13 +0200 39) 	
a286d66f CSVReader.cpp (NubPaws 2022-12-06 23:00:13 +0200 40) 	if (in.eof()) {
a286d66f CSVReader.cpp (NubPaws 2022-12-06 23:00:13 +0200 41) 		in.close();
a286d66f CSVReader.cpp (NubPaws 2022-12-06 23:00:13 +0200 42) 	}
a286d66f CSVReader.cpp (NubPaws 2022-12-06 23:00:13 +0200 43) 	
a286d66f CSVReader.cpp (NubPaws 2022-12-06 23:00:13 +0200 44) 	const std::string delimeter = ",";
a286d66f CSVReader.cpp (NubPaws 2022-12-06 23:00:13 +0200 45) 	
03dbc67e CSVReader.cpp (NubPaws 2022-12-08 17:08:21 +0200 46) 	size_t pos;
a286d66f CSVReader.cpp (NubPaws 2022-12-06 23:00:13 +0200 47) 	std::string token;
a286d66f CSVReader.cpp (NubPaws 2022-12-06 23:00:13 +0200 48) 	while ((pos = ln.find(delimeter)) != std::string::npos) {
a286d66f CSVReader.cpp (NubPaws 2022-12-06 23:00:13 +0200 49) 		token = ln.substr(0, pos);
a286d66f CSVReader.cpp (NubPaws 2022-12-06 23:00:13 +0200 50) 		line.push_back(token);
a286d66f CSVReader.cpp (NubPaws 2022-12-06 23:00:13 +0200 51) 		ln.erase(0, pos + delimeter.length());
a286d66f CSVReader.cpp (NubPaws 2022-12-06 23:00:13 +0200 52) 	}
a286d66f CSVReader.cpp (NubPaws 2022-12-06 23:00:13 +0200 53) 	line.push_back(ln);
a286d66f CSVReader.cpp (NubPaws 2022-12-06 23:00:13 +0200 54) }
