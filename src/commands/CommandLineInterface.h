#ifndef _COMMAND_LINE_INTERFACE_H
#define _COMMAND_LINE_INTERFACE_H

#include <memory>

#include "DefaultIO.h"
#include "KNearestNeighbors.h"
#include "VectorDataSet.h"

class CommandLineInterface {
private:
	DefaultIO* io;
	KNearestNeighbors knn;
	VectorDataSet train;
	VectorDataSet test;
public:
	CommandLineInterface(DefaultIO* io);
	
	void start();
};

typedef CommandLineInterface CLI;

#endif // _COMMAND_LINE_INTERFACE_H
