#ifndef _SOCKET_CONVERSION_H
#define _SOCKET_CONVERSION_H

#include "Types.h"

namespace Socket {
	
	/**
	 * @brief Converts the size_t into network format.
	 * Basically turns it into big endian if it is not
	 * already in that endian.
	 * 
	 * @param host The data to convert.
	 * @return size_t The converted data.
	 */
	size_t toNetwork(size_t host);
	
	/**
	 * @brief Converts the size_t into client format.
	 * Basically turns it into big or small endian if
	 * it is not already in that endian.
	 * 
	 * @param host The data to convert.
	 * @return size_t The converted data.
	 */
	size_t toClient(size_t net);
	
}

#endif // _SOCKET_CONVERSION_H
