#ifndef _SOCKET_CONVERSION_H
#define _SOCKET_CONVERSION_H

#include "Types.h"

namespace Socket {
	
	size_t toNetwork(size_t host);
	
	size_t toClient(size_t net);
	
}

#endif // _SOCKET_CONVERSION_H
