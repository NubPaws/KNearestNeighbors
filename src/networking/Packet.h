#ifndef _PACKET_H
#define _PACKET_H

#include <vector>
#include <string>

#include "Types.h"

namespace Socket {
	
	class Packet {
	private:
		std::vector<byte> data;
		bool valid;
	public:
		/**
		 * @brief Initialize an empty packet that can be loaded up later.
		*/
		Packet();
		/**
		 * @brief Initialize an empty packet, usually to indicated the status of
		 * a packet request - false to indicate the data was in valid or the connection
		 * which the data was send on was invalid.
		 * 
		 * @param valid Whether or not the connection the packet was sent on was valid.
		*/
		Packet(bool valid);
		/**
		 * @brief Initialize a packet with a string as it's date. This constructor converts
		 * the string into it's bytes array to be later sent.
		 * 
		 * @param line The line of data to be packed.
		*/
		Packet(const std::string& line);
		Packet(const char *str);
		/**
		 * @brief Initializes a packet with the array of bytes given to it.
		 * 
		 * @param line The line of data to be packed.
		 * @param size The length of the byte array.
		*/
		Packet(const byte* line, const size_t size);
		
		/**
		 * @brief Check whether or not the packet is valid.
		 * 
		 * @return Whether or not the packet is valid.
		*/
		bool isValid() const;
		/**
		 * @brief Get the size of the data in the packet.
		 * 
		 * @return The size of the data that is packed in the packet.
		*/
		int size() const;
		/**
		 * @brief Returns a pointer to the start of the internal packet
		 * vector of bytes.
		 * 
		 * @returns The inner pointer of the packet.
		*/
		const byte* getData() const;
		
		/**
		 * @brief Add a packet to this packet.
		 * 
		 * @param toAdd The packet to be added to this packet.
		*/
		void add(const Packet& toAdd);
		
		/**
		 * @brief Converts the packet to a vector of strings.
		 * 
		 * @return std::vector<std::string>
		*/
		std::vector<std::string> toVector() const;
		/**
		 * @brief Converts the packet to a string.
		 * 
		 * @return std::string
		*/
		std::string toString() const;
		
		/**
		 * @brief Add a packet to this packet.
		 * 
		 * @param toAdd The packet to be added to this packet.
		 * @return This packet.
		*/
		Packet& operator+=(const Packet& toAdd);
		
		/**
		 * @brief Access a specific byte in the packet.
		 * 
		 * @param i The index of the byte.
		 * @return The byte that was accessed.
		*/
		byte operator[](const size_t& i) const;
	};
	
}

#endif // _PACKET_H
