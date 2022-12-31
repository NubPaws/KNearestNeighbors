#include <cinttypes>

#include "SocketConversion.h"
#include "Types.h"

static bool isBigEndian() {
	std::uint64_t val = 1;
	byte *b = (byte*)&val;
	return b[0] == 0;
}

namespace Socket {
	
	size_t toNetwork(size_t host) {
		if (isBigEndian())
			return host;
		
		size_t result = 0;
		byte *b = (byte*)&host;
		const size_t s = sizeof(size_t);
		
		for (size_t i = 0; i < s; i++) {
			result |= (b[i] << (sizeof(byte) * i));
		}
		
		return result;
	}
	
	size_t toClient(size_t net) {
		return toNetwork(net);
	}
	
}
