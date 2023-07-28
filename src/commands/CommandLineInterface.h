#ifndef _COMMAND_LINE_INTERFACE_H
#define _COMMAND_LINE_INTERFACE_H

#include <memory>

#include "DefaultIO.h"
#include "KNearestNeighbors.h"
#include "VectorDataSet.h"

class CommandLineInterface {
public:
	enum class Option : size_t {
		Empty = 0, Upload = 1, Settings = 2, Classifiy = 3, Display = 4, Download = 5, Exit = 8
	};
private:
	DefaultIO* io;
	KNearestNeighbors knn;
	VectorDataSet train;
	VectorDataSet test;
public:
	/**
	 * @brief Construct a new Command Line Interface object.
	 * The object can be used to execute commands with a
	 * specified io file.
	 * 
	 * @param io The pointer to the DefaultIO to be used when
	 * reading/writing the file. Note that the file does not
	 * take the ownership on the pointer. Meaning that the ptr
	 * must exists as long as the instance exists to avoid
	 * undefined behaviours.
	 */
	CommandLineInterface(DefaultIO* io);
	
	/**
	 * @brief Executes the main loop for the interface.
	 * The loop handles executing the proper commands.
	 */
	void start();
};

typedef CommandLineInterface CLI;

#endif // _COMMAND_LINE_INTERFACE_H
