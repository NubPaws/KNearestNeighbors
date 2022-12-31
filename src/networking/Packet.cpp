#include <sstream>
#include <string>
#include <vector>

#include "Packet.h"

namespace Socket {
	
	Packet::Packet()
		: valid(true), data() {
		
	}
	
	Packet::Packet(bool valid)
		: valid(valid), data() {
		
	}
	
	Packet::Packet(const std::string& line)
		: valid(true), data() {
		
		const char *str = line.c_str();
		
		data.reserve(line.size());
		data.insert(data.end(), str, str + line.size());
	}
	
	Packet::Packet(const byte* line, const size_t size)
		: valid(true), data() {
		
		data.reserve(size);
		data.insert(data.end(), line, line + size);
	}
	
	bool Packet::isValid() const {
		return valid;
	}
	
	int Packet::size() const {
		return data.size();
	}
	
	const byte* Packet::getData() const {
		return data.data();
	}
	
	void Packet::add(const Packet& toAdd) {
		data.reserve(data.size() + toAdd.data.size());
		data.insert(data.end(), toAdd.data.begin(), toAdd.data.end());
	}
	
	std::vector<std::string> Packet::toVector() const {
		std::vector<std::string> vec;
		
		std::istringstream iss(std::string(data.begin(), data.end()));
		
		std::string str;
		while (iss >> str) {
			vec.push_back(str);
		}
		
		return vec;
	}
	
	std::string Packet::toString() const {
		return std::string(data.begin(), data.end());
	}
	
	Packet& Packet::operator+=(const Packet& toAdd) {
		add(toAdd);
		return *this;
	}
	
	byte Packet::operator[](const size_t& i) const {
		return data[i];
	}
	
}
