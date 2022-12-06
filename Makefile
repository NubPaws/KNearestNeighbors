# Choose the compiler.
CC=g++
# Have the right clean command.
ifeq ($(OS),Windows_NT)
	CLN=del
else
	CLN=rm
endif

BUILD_FILES = VectorDistanceCalculator.o
BUILD_FILES += VectorDataSet.o
BUILD_FILES += KNearestNeighbors.o
BUILD_FILES += StringValidator.o
BUILD_FILES += CommandLineArguments.o
BUILD_FILES += CSVReader.o

build: $(BUILD_FILES) Program.o
	$(CC) $(BUILD_FILES) Program.o

# Make sure that when a header file is changed, the c file is recompiled
%.o: %.cpp %.h
	$(CC) -c -o $@ $<

Program.o: Program.cpp
	$(CC) -c Program.cpp

clean:
	$(CLN) *.o a.out a.exe
